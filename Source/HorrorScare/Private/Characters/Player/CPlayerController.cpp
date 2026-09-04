// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/CPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/CJumpScareWidget.h"

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (JumpScareWidgetClass)
	{
		JumpScareWidget = CreateWidget<UCJumpScareWidget>(this, JumpScareWidgetClass);
		if (JumpScareWidget)
		{
			JumpScareWidget->AddToViewport(100);
		}
	}
}

void ACPlayerController::TriggerJumpScare()
{
	if (!JumpScareWidget)
	{
		JumpScareWidget->PlayJumpScare();
	}
}
