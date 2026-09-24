// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/CPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/CJumpScareWidget.h"
#include "Widgets/CJumpScareWidget.h"
#include "Camera/PlayerCameraManager.h"
#include "Widgets/CGameOverWidget.h"


void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeWidget();
}


void ACPlayerController::ShowGameOverSequence()
{
	if (PlayerCameraManager)
	{
		PlayerCameraManager->StartCameraFade(0.f, 1.f, FadeToBlackDuration, FLinearColor::Black, 
			false, true);
	}
	
	GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, this, &ACPlayerController::ShowGameOverWidget, 
		FadeToBlackDuration, false);
}

void ACPlayerController::ShowGameOverWidget()
{
	if (!GameOverWidgetClass) return;
	GameOverWidget = CreateWidget<UCGameOverWidget>(this, GameOverWidgetClass);
	if (GameOverWidget)
	{
		GameOverWidget->AddToViewport(200);
		
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ACPlayerController::TriggerJumpScare()
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerJumpScare"));
	if (!JumpScareWidget) return;
	JumpScareWidget->PlayJumpScare();
	UE_LOG(LogTemp, Warning, TEXT("JumpScareWidget"));
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
