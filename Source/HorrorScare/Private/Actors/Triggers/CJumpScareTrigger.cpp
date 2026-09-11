// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/CJumpScareTrigger.h"

#include "Characters/CCharacter.h"
#include "Characters/Player/CPlayerController.h"
#include "Widgets/CJumpScareWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACJumpScareTrigger::ACJumpScareTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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
	
	// Assumes your HUD widget instance is cached somewhere accessible,
	// e.g. on your custom PlayerController.
	//if (UUserWidget* HUDWidget = PC->GetHUD() ? nullptr : nullptr) {} // placeholder, see note below
	
	if (bMoveAfterTeleport)
	{
		MoveStartLocation = TeleportLocation;
		MoveElaspedTime = 0.f;
		bIsMoving = true;
	}
	
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
	
}

void ACJumpScareTrigger::ResetCooldown()
{
	bIsOnCooldown = false;
}

// Called every frame
void ACJumpScareTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsMoving)
	{
		MoveElaspedTime += DeltaTime;
		float Alpha = FMath::Clamp(MoveElaspedTime / MoveDuration, 0.f, 1.f);
		
		FVector NewLocation = FMath::Lerp(MoveStartLocation, MoveTargetLocation, Alpha);
		SetActorLocation(NewLocation);
		
		DrawDebugSphere(GetWorld(), NewLocation, 50.f, 12, FColor::Red, false, 0.1f);
		UE_LOG(LogTemp, Warning, TEXT("Trigger moving: Alpha=%.2f, Location=%s"), Alpha,*NewLocation.ToString())
		
		if (Alpha >= 1.f)
		{
			bIsMoving = false;
			UE_LOG(LogTemp, Warning, TEXT("Trigger movement finished!"))
		}
	}

}

