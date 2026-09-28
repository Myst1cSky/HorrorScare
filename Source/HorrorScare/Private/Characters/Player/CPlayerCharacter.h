// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CPlayerCharacter.generated.h"

/**
 * 
 */

class UAudioComponent;
class USpotLightComponent;
class USoundBase;
class ACJumpScareEnemy;

UCLASS()
class ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;  
	
	//-----------------------------------------------------//
	//                     Input                          //
	//----------------------------------------------------//
private:
	void HandleLookInput(const struct  FInputActionValue& InputActionValue);
	void HandleMoveInput(const struct  FInputActionValue& InputActionValue);
	
	FVector GetRightDirection() const;
	FVector GetLookFwdDirection() const;
	FVector GetMoveFwdDirection() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* GameplayMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "DebugInput")
	UInputAction* DebugJumpScareAction;
	
	//-----------------------------------------------------//
	//                     Movement                       //
	//----------------------------------------------------//
	
protected:
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaDrainRate = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRegenRate = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRegenDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MinStaminaToSprint = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 700.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina;

	bool bIsSprinting = false;
	float TimeSinceStoppedSprinting = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintInputAction;

	void StartSprint();
	void StopSprint();
	void UpdateStamina(float DeltaTime);
	void DebugTriggerJumpScare();
	void UpdateStaminaWidget();

public:
	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStaminaPercent() const { return MaxStamina > 0.0f ? CurrentStamina / MaxStamina : 0.0f; }
	
	//-----------------------------------------------------//
	//                     Audio                          //
	//----------------------------------------------------//
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* HeartbeatAudioCom;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* HeartbeatSound;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MinHeartbeatDistance = 300.f;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MaxHeartbeatDistance = 1500.f;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MinHeartbeatPitch = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MaxHeartbeatPitch = 1.4f;
	
	UPROPERTY()
	TArray<ACJumpScareEnemy*> CachedEnemies;
	
	void UpdateHeartbeat();
	float GetDistanceToNearestEnemy() const;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopHeartbeat();
	
	//-----------------------------------------------------//
	//                     Flashlight                     //
	//----------------------------------------------------//
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Flashlight")
	USpotLightComponent* Flashlight;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FlashlightInputAction;
	
	UPROPERTY(EditAnywhere, Category = "Flashlight")
	USoundBase* FlashlightSound;
	
	bool bIsFlashlightOn = false;
	bool bFlashlightLocked = false;
	
	void ToggleFlashlight();
	void UpdateFlashlightRotation();
	
public:
	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void DisableFlashlight();
};
