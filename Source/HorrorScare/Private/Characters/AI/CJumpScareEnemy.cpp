// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CJumpScareEnemy.h"

#include "Characters/Player/CPlayerController.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SGameLayerManager.h"
#include "Splines/SplineMath.h"

// Sets default values
ACJumpScareEnemy::ACJumpScareEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACJumpScareEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CachedPlayer = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
}

// Called every frame
void ACJumpScareEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForCatch();

}

void ACJumpScareEnemy::CheckForCatch()
{
	if (bHasCaughtPlayer || !CachedPlayer) return;
	
	const float DistSquared = FVector::DistSquared(GetActorLocation(), CachedPlayer->GetActorLocation());
	if (DistSquared > FMath::Square(CatchRadius)) return;
	
	bHasCaughtPlayer = true;
	
	if (ACPlayerController* PC = Cast<ACPlayerController>(CachedPlayer->GetController()))
	{
		PC->TriggerJumpScare();
	}
	
	if (AAIController* AICon = Cast<AAIController>(GetController()))
	{
		if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(AICon->GetRootComponent()))
		{
			BTComp->StopTree(EBTStopMode::Safe);
		}
	
		// TODO: disable AI movement / player input / handle "caught" state here
	}
}

