// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CJumpScareEnemyController.h"
#include "Characters/CCharacter.h"
#include "Perception/AIPerceptionTypes.h"


ACJumpScareEnemyController::ACJumpScareEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = 800.f;
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ACJumpScareEnemyController::BeginPlay()
{
	Super::BeginPlay();
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACJumpScareEnemyController::OnTargetPerceived);
}

void ACJumpScareEnemyController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (Cast<ACCharacter>(Actor))
	{
		PlayerTarget = Stimulus.WasSuccessfullySensed() ? Actor : nullptr;
	}
}

void ACJumpScareEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerTarget)
	{
		MoveToActor(PlayerTarget, 30.f);
	}
}



