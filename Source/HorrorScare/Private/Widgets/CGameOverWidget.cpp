// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CGameOverWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UCGameOverWidget::OnRestartBClicked);
	}
	
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UCGameOverWidget::OnQuitBClicked);
	}
}

void UCGameOverWidget::OnRestartBClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->ResetIgnoreMoveInput();
		PC->ResetIgnoreLookInput();
	}
	
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}

void UCGameOverWidget::OnQuitBClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
