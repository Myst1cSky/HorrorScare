// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CJumpScareEnemy.generated.h"

UCLASS()
class ACJumpScareEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACJumpScareEnemy();
	
	UPROPERTY(EditAnywhere, Category = "JumpScare")
	float CatchRadius = 100.f;
	
	bool bHasCaughtPlayer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void CheckForCatch();
	
};
