// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimationBlenderWidget.generated.h"

/**
 * 
 */
UCLASS()
class GLBPROJECT_API UAnimationBlenderWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
    UFUNCTION(BlueprintCallable)
    void OnLoadAnimation1Clicked();

    UFUNCTION(BlueprintCallable)
    void OnLoadAnimation2Clicked();

    UFUNCTION(BlueprintCallable)
    void OnBlendFactorChanged(float Value);

    UFUNCTION(BlueprintCallable)
    void OnSaveResultClicked();

private:
    UPROPERTY()
    class AGLBAnimationBlender* AnimationBlender;
};
};
