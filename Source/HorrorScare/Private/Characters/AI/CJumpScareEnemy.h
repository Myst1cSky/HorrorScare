// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	FTimerHandle CatchAnimTimerHandle;
	
	bool bHasCaughtPlayer = false;
	
	UPROPERTY()
	ACharacter* CachedPlayer;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime ) override;
	
	void CheckForCatch();
	void TriggerCatchSequence(ACharacter* Player);
	
	UFUNCTION()
	void PlayHitMontage();
	
	UFUNCTION()
	void OnHitMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
