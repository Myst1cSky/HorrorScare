// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/CJumpScareTrigger.h"

#include "Characters/CCharacter.h"
#include "Characters/Player/CPlayerController.h"
#include "Widgets/CJumpScareWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//#include "CJumpScareLocationManager.h"

// Sets default values
ACJumpScareTrigger::ACJumpScareTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetBoxExtent(FVector(10.f, 100.f, 100.f));
	TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));

}

void ACJumpScareTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedCom, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (bTriggerOnce && bHasTriggered) return;
	if (bIsOnCooldown) return;
	
	ACCharacter* Player = Cast<ACCharacter>(OtherActor);
	if (!Player || !Player->IsPlayerControlled()) return;
	
	bHasTriggered = true;
	bIsOnCooldown = true;
	
	ACPlayerController* PC = Cast<ACPlayerController>(Player->GetController());
	if (!PC) return;
	//
	PC->TriggerJumpScare();
	
	/*if (UCJumpScareLocationManager* LocationManager = GetWorld()->GetSubsystem<UCJumpScareLocationManager>())
	{
		// Free up the spot this trigger is currently sitting on
		LocationManager->ReleaseLocation(CurrentLocationSlot);

		FVector NewLocation;
		if (LocationManager->RequestRandomLocation(NewLocation))
		{
			CurrentLocationSlot = NewLocation;
			SetActorLocation(NewLocation);

			DrawDebugSphere(GetWorld(), NewLocation, 50.0f, 12, FColor::Red, true, -1.0f, 0, 2.0f);
		}
	}*/
	
	UE_LOG(LogTemp, Warning, TEXT("Trigger location BEFORE teleport: %s"), *GetActorLocation().ToString());
	//SetActorLocation(TeleportLocation);
	UE_LOG(LogTemp, Warning, TEXT("Trigger location AFTER teleport: %s"), *GetActorLocation().ToString()); 
	//DrawDebugSphere(GetWorld(), TeleportLocation, 50.f, 12, FColor::Red, true, -1.f, 0, 2.f);
	
	if (!bTriggerOnce)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ACJumpScareTrigger::ResetCooldown,
			CooldownDuration,false);
	}
}

// Called when the game starts or when spawned
void ACJumpScareTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACJumpScareTrigger::OnOverlapBegin);
	
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50.f, 12, 
		FColor::Green, true, -1.f, 0, 2.f);
	
	CurrentLocationSlot = GetActorLocation();

	/*if (UCJumpScareLocationManager* LocationManager = GetWorld()->GetSubsystem<UCJumpScareLocationManager>())
	{
		LocationManager->OccupiedLocations.Add(CurrentLocationSlot);
	}*/
}

void ACJumpScareTrigger::ResetCooldown()
{
	bIsOnCooldown = false;
}

// Called every frame
void ACJumpScareTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

