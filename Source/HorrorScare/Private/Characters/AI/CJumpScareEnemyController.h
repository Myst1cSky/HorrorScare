// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CJumpScareEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class ACJumpScareEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACJumpScareEnemyController();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAISenseConfig_Sight* SightConfig;
	
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);
	
	AActor* PlayerTarget;
	
	virtual void Tick(float DeltaTime) override;
	
};
