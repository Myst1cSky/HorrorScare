// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CBBTTask_FindRandomPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UCBBTTask_FindRandomPatrolPoint::UCBBTTask_FindRandomPatrolPoint()
{
	NodeName = TEXT("Find Random Patrol Point");
}

EBTNodeResult::Type UCBBTTask_FindRandomPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;
	
	APawn* Pawn = AICon->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(AICon->GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;

	FNavLocation ResultLocation;
	bool bFound = NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), WanderRadius, ResultLocation);

	if (bFound)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolLocationKey.SelectedKeyName, ResultLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

