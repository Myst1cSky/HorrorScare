// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/CPlayerCharacter.h"
#include "Characters/Player/CPlayerController.h"
#include "Components/AudioComponent.h"
#include "Components/SpotlightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/AI/CJumpScareEnemy.h"
#include "Kismet/GameplayStatics.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(720.f);
	
	HeartbeatAudioCom = CreateDefaultSubobject<UAudioComponent>(TEXT("HeartbeatAudioComponent"));
	HeartbeatAudioCom->SetupAttachment(RootComponent);
	HeartbeatAudioCom->bAutoActivate = false;
	HeartbeatAudioCom->SetVolumeMultiplier(0.f);
	
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(RootComponent);
	Flashlight->SetRelativeLocation(FVector(30.f, 0.f, 60.f));
	Flashlight->Intensity = 5000.f;
	Flashlight->InnerConeAngle = 10.f;
	Flashlight->OuterConeAngle = 25.f;
	Flashlight->AttenuationRadius = 2000.f;
	Flashlight->SetVisibility(false);
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentStamina = MaxStamina;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACJumpScareEnemy::StaticClass(), FoundEnemies);
	for (AActor* Enemy : FoundEnemies)
	{
		if (ACJumpScareEnemy* TypedEnemy = Cast<ACJumpScareEnemy>(Enemy))
		{
			CachedEnemies.Add(TypedEnemy);
		}
		UE_LOG(LogTemp, Warning, TEXT("Cached %d enemies"), CachedEnemies.Num());
		UE_LOG(LogTemp, Warning, TEXT("HeartbeatSound: %s"), HeartbeatSound ? TEXT("valid") : TEXT("NULL"));
		UE_LOG(LogTemp, Warning, TEXT("HeartbeatAudioComponent: %s"), HeartbeatAudioCom ? TEXT("valid") : TEXT("NULL"));
	}
	
	if (HeartbeatSound && HeartbeatAudioCom)
	{
		HeartbeatAudioCom->SetSound(HeartbeatSound);
		HeartbeatAudioCom->Play();
		UE_LOG(LogTemp, Warning, TEXT("HeartbeatAudioComponent->Play() called"));
	}
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateStamina(DeltaTime);
	UpdateStaminaWidget();
	UpdateHeartbeat();
	UpdateFlashlightRotation();
	
}

void ACPlayerCharacter::UpdateStaminaWidget()
{
	ACPlayerController* PC = Cast<ACPlayerController>(GetController());
	if (!PC || !PC->StaminaWidget) return;
	
	const float Percent = GetStaminaPercent();
	const bool bIsDraining = bIsSprinting && !GetVelocity().IsNearlyZero();
	PC->StaminaWidget->UpdateStamina(GetStaminaPercent(), bIsDraining);
			
	FLinearColor Color = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, Percent);
	PC->StaminaWidget->SetFillColor(Color);
}

void ACPlayerCharacter::StopHeartbeat()
{
	if (HeartbeatAudioCom && HeartbeatAudioCom->IsPlaying())
	{
		HeartbeatAudioCom->Stop();
	}
}

void ACPlayerCharacter::ToggleFlashlight()
{
	if (bFlashlightLocked) return;
	
	bIsFlashlightOn = !bIsFlashlightOn;
	Flashlight->SetVisibility(bIsFlashlightOn);
	
	if (FlashlightSound)
	{
		UGameplayStatics::PlaySound2D(this, FlashlightSound);
	}
}

void ACPlayerCharacter::UpdateFlashlightRotation()
{
	if (bIsFlashlightOn)
	{
		Flashlight->SetWorldRotation(GetControlRotation());
	}
}

void ACPlayerCharacter::DisableFlashlight()
{
	bFlashlightLocked = true;
	bIsFlashlightOn = false;
	Flashlight->SetVisibility(false);
}

void ACPlayerCharacter::UpdateHeartbeat()
{
	if (!HeartbeatAudioCom) return;

	const float Distance = GetDistanceToNearestEnemy();
	UE_LOG(LogTemp, Warning, TEXT("Distance to nearest enemy: %.1f"), Distance);

	const float Alpha = 1.0f - FMath::Clamp(
		(Distance - MinHeartbeatDistance) / (MaxHeartbeatDistance - MinHeartbeatDistance), 0.0f, 1.0f);

	HeartbeatAudioCom->SetVolumeMultiplier(Alpha);
	HeartbeatAudioCom->SetPitchMultiplier(FMath::Lerp(MinHeartbeatPitch, MaxHeartbeatPitch, Alpha));
}

float ACPlayerCharacter::GetDistanceToNearestEnemy() const
{
	float ClosestDistSquared = TNumericLimits<float>::Max();

	for (const ACJumpScareEnemy* Enemy : CachedEnemies)
	{
		if (!Enemy) continue;

		const float DistSquared = FVector::DistSquared(GetActorLocation(), Enemy->GetActorLocation());
		if (DistSquared < ClosestDistSquared)
		{
			ClosestDistSquared = DistSquared;
		}
	}
	
	return FMath::Sqrt(ClosestDistSquared);
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
		if (FlashlightInputAction)
		{
			EnhancedInputComponent->BindAction(FlashlightInputAction, ETriggerEvent::Started, this, &ACPlayerCharacter::ToggleFlashlight);
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

void ACPlayerCharacter::DebugTriggerJumpScare()
{
	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		PC->TriggerJumpScare();
	}
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
