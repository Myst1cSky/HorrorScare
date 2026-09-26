// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CStaminaWidget.h"

void UCStaminaWidget::UpdateStamina(float Percent)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}
}

void UCStaminaWidget::SetFillColor(FLinearColor NewColor)
{
	if (StaminaBar)
	{
		StaminaBar->SetFillColorAndOpacity(NewColor);
	}
}
