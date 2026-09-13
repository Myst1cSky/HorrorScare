// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/JumpScareLocationManager/CJumpScaceLocationManager.h"

void UCJumpScaceLocationManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	AllLocations.Empty();
	OccupiedLocations.Empty();

	TArray<AActor*> FoundPoints;
	//UGameplayStatics::GetAllActorsOfClass(&InWorld, ACJumpScareLocationPoint::StaticClass(), FoundPoints);

	for (AActor* Point : FoundPoints)
	{
		if (Point)
		{
			AllLocations.Add(Point->GetActorLocation());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("JumpScareLocationManager found %d location points"), AllLocations.Num());
}

bool UCJumpScaceLocationManager::RequestRandomLocation(FVector& OutLocation)
{
	TArray<FVector> FreeLocations;
	for (const FVector& Loc : AllLocations)
	{
		if (!OccupiedLocations.Contains(Loc))
		{
			FreeLocations.Add(Loc);
		}
	}
	if (FreeLocations.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No free JumpScare locations available"));
		return false;
	}
	int32 RandomIndex = FMath::RandRange(0, FreeLocations.Num() - 1);
	OutLocation = FreeLocations[RandomIndex];
	OccupiedLocations.Add(OutLocation);
	return true;
}

void UCJumpScaceLocationManager::ReleaseLocation(const FVector& Location)
{
	OccupiedLocations.Remove(Location);
}

void UCJumpScaceLocationManager::MarkLocationOccupied(const FVector& Location)
{
	OccupiedLocations.AddUnique(Location);
}
