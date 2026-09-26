// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CStaminaWidget.generated.h"

/**
 * 
 */
UCLASS()
class UCStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;
	
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void UpdateStamina(float Percent);
	
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetFillColor(FLinearColor NewColor);
};
