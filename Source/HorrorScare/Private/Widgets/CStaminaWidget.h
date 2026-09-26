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
	
	UPROPERTY(Transient, meta = (BindWidgetAnim), BlueprintReadOnly)
	UWidgetAnimation* LowStaminaBlink;
	
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void UpdateStamina(float Percent, bool bIsDraining);
	
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetFillColor(FLinearColor NewColor);
	
protected:
	bool bIsBlinking = false;
};
