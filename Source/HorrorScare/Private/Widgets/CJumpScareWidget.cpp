// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CJumpScareWidget.h"
#include "Kismet/GameplayStatics.h"

void UCJumpScareWidget::PlayJumpScare()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayJumpScare called"));
	if (ScareImage)
	{
		UE_LOG(LogTemp, Warning, TEXT("JumpScare Image set to visible"))
		ScareImage->SetVisibility(ESlateVisibility::Visible);
	}
	FWidgetAnimationDynamicEvent AnimFinishedDelegate;
	AnimFinishedDelegate.BindUFunction(this, TEXT("OnJumpScareAnimFinished"));
	BindToAnimationFinished(JumpScareAnim, AnimFinishedDelegate);
	if (JumpScareAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("JumpScareAnim playing"));
		PlayAnimation(JumpScareAnim);
	}
	if (ScareSound)
	{
		UGameplayStatics::PlaySound2D(this, ScareSound);
	}
}

void UCJumpScareWidget::OnJumpScareAnimFinished()
{
	if (ScareImage)
	{
		ScareImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCJumpScareWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ScareImage)
	{
		ScareImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
