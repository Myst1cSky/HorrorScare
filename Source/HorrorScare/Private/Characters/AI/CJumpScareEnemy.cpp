// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CJumpScareEnemy.h"

#include "Characters/Player/CPlayerController.h"
#include "Kismet/GameplayStatics.h"

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
	
}

// Called every frame
void ACJumpScareEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForCatch();

}

void ACJumpScareEnemy::CheckForCatch()
{
	if (bHasCaughtPlayer) return;
	
	ACharacter* Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Player) return;
	
	float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	if (Distance <= CatchRadius)
	{
		bHasCaughtPlayer = true;
		
		if (ACPlayerController* PC = Cast<ACPlayerController>(Player->GetController()))
		{
			PC->TriggerJumpScare();
		}
		// TODO: disable AI movement / player input / handle "caught" state here
	}
}

