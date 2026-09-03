// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CJumpScareWidget.h"
#include "Kismet/GameplayStatics.h"

void UCJumpScareWidget::PlayJumpScare()
{
	if (JumpScareAnim)
	{
		PlayAnimation(JumpScareAnim);
	}
	
	if (ScareSound)
	{
		UGameplayStatics::PlaySound2D(this, ScareSound);
	}
}
