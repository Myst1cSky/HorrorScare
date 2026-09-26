// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/CJumpScareWidget.h"
#include "Widgets/CStaminaWidget.h"
#include "CPlayerController.generated.h"

/**
 * 
 */

class UCGameOverWidget;

UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameOver")
	TSubclassOf<UCGameOverWidget> GameOverWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "GameOver")
	UCGameOverWidget* GameOverWidget;

	UPROPERTY(EditDefaultsOnly, Category = "GameOver")
	float FadeToBlackDuration = 1.5f;

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	void ShowGameOverSequence();
	
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UCJumpScareWidget> JumpScareWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	UCJumpScareWidget* JumpScareWidget;
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void TriggerJumpScare();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UCStaminaWidget> StaminaWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	UCStaminaWidget* StaminaWidget;
	
	UFUNCTION()
	void InitializeWidget();
	
protected:
	FTimerHandle GameOverTimerHandle;
	
	UFUNCTION()
	void ShowGameOverWidget();
	
	virtual void BeginPlay() override;
};
