// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CJumpScaceLocationManager.generated.h"

/**
 * 
 */
UCLASS()
class UCJumpScaceLocationManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;;
	
	UFUNCTION(BlueprintCallable, Category = "JumpScare")
	bool RequestRandomLocation(FVector& OutLocation);
	
	UFUNCTION(BlueprintCallable, Category = "JumpScare")
	void ReleaseLocation(const FVector& Location);
	
	UFUNCTION(BlueprintCallable, Category = "JumpScare")
	void MarkLocationOccupied(const FVector& Location);
	
private:
	UPROPERTY()
	TArray<FVector> AllLocations;
	
	UPROPERTY()
	TArray<FVector> OccupiedLocations;
};
