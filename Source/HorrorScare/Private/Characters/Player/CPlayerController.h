// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/CJumpScareWidget.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UCJumpScareWidget> JumpScareWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	UCJumpScareWidget* JumpScareWidget;
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void TriggerJumpScare();
	
protected:
	virtual void BeginPlay() override;
};
