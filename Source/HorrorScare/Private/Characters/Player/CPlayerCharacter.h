// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CPlayerCharacter.generated.h"

/**
 * 
 */
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
	class UInputAction* SprintInputAction;

	void StartSprint();
	void StopSprint();
	void UpdateStamina(float DeltaTime);

public:
	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStaminaPercent() const { return MaxStamina > 0.0f ? CurrentStamina / MaxStamina : 0.0f; }
	
};
