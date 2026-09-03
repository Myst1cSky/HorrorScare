// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CJumpScareTrigger.generated.h"

UCLASS()
class ACJumpScareTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACJumpScareTrigger();

protected:
	// Called when the game starts or when spawned
	
	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UBoxComponent* TriggerVolume;
	
	UPROPERTY(EditAnywhere, Category = "JumpScare")
	bool bTriggerOnce = true;
	
	bool bHasTriggered = false;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedCom, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
