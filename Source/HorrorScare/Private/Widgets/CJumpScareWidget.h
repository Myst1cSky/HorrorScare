// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/WidgetAnimation.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Sound/SoundBase.h"
#include "CJumpScareWidget.generated.h"

/**
 * 
 */
UCLASS()
class UCJumpScareWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UImage* ScareImage;
	
	// Widget Anim "we" create in the UMG Designer timeline
	UPROPERTY(Transient, meta = (BindWidgetAnim), BlueprintReadOnly)
	UWidgetAnimation* JumpScareAnim;
	
	UPROPERTY(EditDefaultsOnly, Category = "JumpScare")
	USoundBase* ScareSound;
	
	UFUNCTION(BlueprintCallable, Category = "JumpScare")
	void PlayJumpScare();
	
	UFUNCTION()
	void OnJumpScareAnimFinished();
};
