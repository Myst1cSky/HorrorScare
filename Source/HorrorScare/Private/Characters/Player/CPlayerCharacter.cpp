// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/CPlayerCharacter.h"
#include "Characters/Player/CPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(720.f);
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentStamina = MaxStamina;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateStamina(DeltaTime);
	
	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		if (PC->StaminaWidget)
		{
			const float Percent = GetStaminaPercent();
			const bool bIsDraining = bIsSprinting && !GetVelocity().IsNearlyZero();
			PC->StaminaWidget->UpdateStamina(GetStaminaPercent(), bIsDraining);
			
			FLinearColor Color = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, Percent);
			PC->StaminaWidget->SetFillColor(Color);
		}
	}
}

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = 
		GetController<ACPlayerController>()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	if (EnhancedInputLocalPlayerSubsystem)
	{
		EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(GameplayMappingContext, 0);
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);
		if (SprintInputAction)
		{
			EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Started, this, &ACPlayerCharacter::StartSprint);
			EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::StopSprint);
			EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Canceled, this, &ACPlayerCharacter::StopSprint);
		}
		if (DebugJumpScareAction)
		{
			EnhancedInputComponent->BindAction(DebugJumpScareAction, ETriggerEvent::Started, this, &ACPlayerCharacter::DebugTriggerJumpScare);
		}
	}
}


void ACPlayerCharacter::HandleLookInput(const struct FInputActionValue& InputActionValue)
{
	FVector2D InputAction = InputActionValue.Get<FVector2D>();
	AddControllerYawInput(InputAction.X);
	AddControllerPitchInput(InputAction.Y);
}

void ACPlayerCharacter::HandleMoveInput(const struct FInputActionValue& InputActionValue)
{
	FVector2D InputAction = InputActionValue.Get<FVector2D>();
	InputAction.Normalize();
	
	AddMovementInput(GetMoveFwdDirection() * InputAction.Y + GetRightDirection() * InputAction.X);
}

FVector ACPlayerCharacter::GetRightDirection() const
{
	return GetActorRightVector();
}

FVector ACPlayerCharacter::GetLookFwdDirection() const
{
	return GetActorForwardVector();
}

FVector ACPlayerCharacter::GetMoveFwdDirection() const
{
	return FVector::CrossProduct(GetRightDirection(), FVector::UpVector);
}

void ACPlayerCharacter::StartSprint()
{
	if (CurrentStamina <= MinStaminaToSprint) return;
	
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACPlayerCharacter::StopSprint()
{
	bIsSprinting = false;
	TimeSinceStoppedSprinting = 0.f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayerCharacter::UpdateStamina(float DeltaTime)
{
	if (bIsSprinting)
	{
		const bool bIsMoving = !GetVelocity().IsNearlyZero();
		
		if (bIsMoving)
		{
			CurrentStamina = FMath::Max(0.f, CurrentStamina - StaminaDrainRate * DeltaTime);
			
			if (CurrentStamina <= 0.f)
			{
				StopSprint();
			}
		}
	}
	else
	{
		TimeSinceStoppedSprinting += DeltaTime;
		
		if (TimeSinceStoppedSprinting >= StaminaRegenDelay)
		{
			CurrentStamina = FMath::Min(MaxStamina, CurrentStamina + StaminaRegenRate * DeltaTime);
		}
	}
}

// New function on your character, since input usually lives there in Enhanced Input setups
void ACCharacter::DebugTriggerJumpScare()
{
	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		PC->TriggerJumpScare();
	}
}