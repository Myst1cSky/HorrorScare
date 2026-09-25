// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/CPlayerController.h"
#include "GameFramework/Character.h"
#include "CJumpScareEnemy.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class ACJumpScareEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACJumpScareEnemy();
	
	UPROPERTY(EditAnywhere, Category = "JumpScare")
	float CatchRadius = 100.f;

protected:
	UPROPERTY(VisibleAnywhere, Category = "JumpScare Catch")
	USpringArmComponent* CatchCameraArm;
	
	UPROPERTY(VisibleAnywhere, Category = "JumpScare Catch")
	UCameraComponent* CatchCamera;
	
	UPROPERTY(EditAnywhere, Category = "JumpScare Catch")
	TArray<UAnimMontage*> HitMontages;
	
	UPROPERTY(EditAnywhere, Category = "JumpScare Catch")
	float CameraBlendTime = .75f;
	
	UPROPERTY(EditAnywhere, Category = "JumpScare Catch")
	float AnimationDelay = 1.f;
	
	UPROPERTY()
	ACharacter* CachedPlayer;
	
	UPROPERTY()
	ACPlayerController* CachedPC;
	
	UFUNCTION()
	void PlayHitMontage();
	
	UFUNCTION()
	void OnHitMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	FTimerHandle CatchAnimTimerHandle;
	
	bool bHasCaughtPlayer = false;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime ) override;
	
	void CheckForCatch();
	void TriggerCatchSequence();
	
};
