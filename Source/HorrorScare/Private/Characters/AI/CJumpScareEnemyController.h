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

class UBehaviorTree;
class UBehaviorTreeComponent;

UCLASS()
class ACJumpScareEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACJumpScareEnemyController();
	
	UPROPERTY(EditAnywhere, Category= "AI")
	UBehaviorTree* BehaviorTree;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAISenseConfig_Sight* SightConfig;
	
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);
	
	AActor* PlayerTarget;
	
	virtual void Tick(float DeltaTime) override;
	
};
