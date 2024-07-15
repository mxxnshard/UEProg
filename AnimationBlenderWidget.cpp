// Fill out your copyright notice in the Description page of Project Settings.



#include "AnimationBlenderWidget.h"
#include "AnimationBlender.h"
#include "Kismet/GameplayStatics.h"


void UAnimationBlenderWidget::OnLoadAnimation1Clicked()
{
    FString FilePath = FPaths::ProjectContentDir() + TEXT("Animations/Animation1.glb");
    AnimationBlender->LoadGLBAnimations(FilePath, TEXT(""));
}

void UAnimationBlenderWidget::OnLoadAnimation2Clicked()
{
    FString FilePath = FPaths::ProjectContentDir() + TEXT("Animations/Animation2.glb");
    AnimationBlender->LoadGLBAnimations(TEXT(""), FilePath);
}

void UAnimationBlenderWidget::OnBlendFactorChanged(float Value)
{
    AnimationBlender->SetBlendFactor(Value);
}

void UAnimationBlenderWidget::OnSaveResultClicked()
{
    AnimationBlender->BlendAnimations();
}