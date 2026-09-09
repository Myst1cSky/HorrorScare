// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/CPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/CJumpScareWidget.h"

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeWidget();
}

void ACPlayerController::TriggerJumpScare()
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerJumpScare"));
	if (!JumpScareWidget) return;
	UE_LOG(LogTemp, Warning, TEXT("JumpScareWidget"));
	JumpScareWidget->PlayJumpScare();

}

void ACPlayerController::InitializeWidget()
{
	if (JumpScareWidgetClass)
	{
		JumpScareWidget = CreateWidget<UCJumpScareWidget>(this, JumpScareWidgetClass);
		if (JumpScareWidget)
		{
			JumpScareWidget->AddToViewport(100);
			UE_LOG(LogTemp, Warning, TEXT("JumpScareWidget added"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass does not exist"));
	}
}
