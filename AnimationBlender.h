#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimSequence.h"
#include "AnimationBlender.generated.h"

UCLASS()
class GLBPROJECT_API AGLBAnimationBlender : public AActor
{
    GENERATED_BODY()

public:
    AGLBAnimationBlender();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void LoadGLBAnimations(const FString& FilePath1, const FString& FilePath2);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetBlendFactor(float BlendFactor);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void BlendAnimations();

private:
    UAnimSequence* Animation1;
    UAnimSequence* Animation2;
    float BlendFactor;

    void LoadAnimationFromGLB(const FString& FilePath, UAnimSequence*& OutAnimation);
    void InterpolateAnimations();
    FTransform GetBoneTransformFromAnimation(UAnimSequence* Animation, int32 FrameIndex);
    void SetInterpolatedBoneTransform(UAnimSequence* Animation, int32 FrameIndex, const FVector& Pos, const FQuat& Rot, const FVector& Scale);
};