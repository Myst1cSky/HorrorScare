// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/CJumpScareTrigger.h"

#include "Characters/CCharacter.h"
#include "Widgets/CJumpScareWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACJumpScareTrigger::ACJumpScareTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	//TriggerVolume->SetBoxEvent(FVector(100.f, 100.f, 100.f));
	TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));

}

void ACJumpScareTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedCom, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (bTriggerOnce && bHasTriggered) return;
	
	ACCharacter* Player = Cast<ACCharacter>(OtherActor);
	if (!Player || !Player->IsPlayerControlled()) return;
	
	bHasTriggered = true;
	
	//ACPlayerController* PC = Cast<ACPlayerController>(Player->GetController());
	//if (!PC) return;
	
	// Assumes your HUD widget instance is cached somewhere accessible,
	// e.g. on your custom PlayerController.
	//if (UUserWidget* HUDWidget = PC->GetHUD() ? nullptr : nullptr) {} // placeholder, see note below
}

// Called when the game starts or when spawned
void ACJumpScareTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACJumpScareTrigger::OnOverlapBegin);
	
}

// Called every frame
void ACJumpScareTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

