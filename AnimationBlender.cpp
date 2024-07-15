#include "AnimationBlender.h"
#include "Animation/AnimSequence.h"
#include "Animation/Skeleton.h"
#include "AnimationRuntime.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Animation/AnimInstance.h"
#include "Animation/AnimTypes.h"
#include "Animation/AnimCurveTypes.h"

AGLBAnimationBlender::AGLBAnimationBlender()
{
    PrimaryActorTick.bCanEverTick = true;
    BlendFactor = 0.5f;
}

void AGLBAnimationBlender::LoadGLBAnimations(const FString& FilePath1, const FString& FilePath2)
{
    LoadAnimationFromGLB(FilePath1, Animation1);
    LoadAnimationFromGLB(FilePath2, Animation2);
}

void AGLBAnimationBlender::SetBlendFactor(float NewBlendFactor)
{
    BlendFactor = FMath::Clamp(NewBlendFactor, 0.0f, 1.0f);
}

void AGLBAnimationBlender::BlendAnimations()
{
    if (Animation1 && Animation2)
    {
        InterpolateAnimations();
    }
}

void AGLBAnimationBlender::LoadAnimationFromGLB(const FString& FilePath, UAnimSequence*& OutAnimation)
{
    Assimp::Importer Importer;
    const aiScene* Scene = Importer.ReadFile(TCHAR_TO_ANSI(*FilePath), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_LimitBoneWeights);

    if (!Scene || !Scene->HasAnimations())
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load GLB animation: %s"), *FilePath);
        return;
    }

    const aiAnimation* Animation = Scene->mAnimations[0];
    OutAnimation = NewObject<UAnimSequence>(this, UAnimSequence::StaticClass());
    OutAnimation->SequenceLength = Animation->mDuration / Animation->mTicksPerSecond;
}

void AGLBAnimationBlender::InterpolateAnimations()
{
    if (Animation1 && Animation2)
    {
        UAnimSequence* BlendedAnimation = NewObject<UAnimSequence>(this);

        int32 NumFrames = FMath::Min(Animation1->GetNumberOfFrames(), Animation2->GetNumberOfFrames());
        BlendedAnimation->NumFrames = NumFrames;


        for (int32 FrameIndex = 0; FrameIndex < NumFrames; ++FrameIndex)
        {

            FTransform BoneTransform1 = GetBoneTransformFromAnimation(Animation1, FrameIndex);
            FTransform BoneTransform2 = GetBoneTransformFromAnimation(Animation2, FrameIndex);

            // »нтерпол€ци€ позиций костей
            FVector InterpolatedPos = FMath::Lerp(BoneTransform1.GetTranslation(), BoneTransform2.GetTranslation(), BlendFactor);

            // »нтерпол€ци€ вращений костей
            FQuat InterpolatedRot = FQuat::Slerp(BoneTransform1.GetRotation(), BoneTransform2.GetRotation(), BlendFactor);

            // »нтерпол€ци€ масштабов костей
            FVector InterpolatedScale = FMath::Lerp(BoneTransform1.GetScale3D(), BoneTransform2.GetScale3D(), BlendFactor);

            // ѕрименение интерполированных значений к новой анимации
            SetInterpolatedBoneTransform(BlendedAnimation, FrameIndex, InterpolatedPos, InterpolatedRot, InterpolatedScale);
        }
    }
}

FTransform AGLBAnimationBlender::GetBoneTransformFromAnimation(UAnimSequence* Animation, int32 FrameIndex)
{
    FCompactPose Pose;
    FBlendedCurve Curve;
    UE::Anim::FStackCustomAttributes Attributes; 
    FAnimExtractContext ExtractContext(FrameIndex, true);
    Animation->GetBonePose(Pose, Curve, ExtractContext, Attributes);

    return Pose[FCompactPoseBoneIndex(0)];
}
void AGLBAnimationBlender::SetInterpolatedBoneTransform(UAnimSequence* Animation, int32 FrameIndex, const FVector& Pos, const FQuat& Rot, const FVector& Scale)
{

    if (!Animation)
    {
        UE_LOG(LogTemp, Warning, TEXT("BlendedAnimation is null."));
        return;
    }

    FRawAnimSequenceTrack NewTrack;
    NewTrack.PosKeys.Add(Pos);
    NewTrack.RotKeys.Add(Rot);
    NewTrack.ScaleKeys.Add(Scale);

    Animation->AddNewRawTrack("Bone_0", &NewTrack);
}