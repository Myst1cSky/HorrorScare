// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LocationPoint/CJumpScareLocationPoint.h"
#include "Components/BillboardComponent.h"

// Sets default values
ACJumpScareLocationPoint::ACJumpScareLocationPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
#if WITH_EDITORONLY_DATA
	EditorIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorIcon"));
	EditorIcon->SetupAttachment(RootComponent);
#endif
}

// Called when the game starts or when spawned
void ACJumpScareLocationPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACJumpScareLocationPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

