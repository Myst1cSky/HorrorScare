// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class UCGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnRestartBClicked();
	
	UFUNCTION()
	void OnQuitBClicked();
};
