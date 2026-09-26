// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CStaminaWidget.h"

void UCStaminaWidget::SetFillColor(FLinearColor NewColor)
{
	if (StaminaBar)
	{
		StaminaBar->SetFillColorAndOpacity(NewColor);
	}
}

void UCStaminaWidget::UpdateStamina(float Percent, bool bIsDraining)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}
	
	const bool bShouldBlink = bIsDraining && Percent <=.25f;
	
	if (bShouldBlink && !bIsBlinking)
	{
		bIsBlinking = true;
		if (LowStaminaBlink)
		{
			PlayAnimation(LowStaminaBlink, 0.f, 0);
		}
	}
	else if (!bShouldBlink && bIsBlinking)
	{
		bIsBlinking = false;
		if (LowStaminaBlink)
		{
			StopAnimation(LowStaminaBlink);
		}
	}
}
