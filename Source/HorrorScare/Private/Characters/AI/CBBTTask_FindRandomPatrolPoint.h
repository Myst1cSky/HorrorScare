// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBBTTask_FindRandomPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class UCBBTTask_FindRandomPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBBTTask_FindRandomPatrolPoint();
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector PatrolLocationKey;
	
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float WanderRadius = 1500.f;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
