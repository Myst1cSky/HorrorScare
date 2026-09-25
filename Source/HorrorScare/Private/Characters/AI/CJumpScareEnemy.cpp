// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CJumpScareEnemy.h"

#include "Characters/Player/CPlayerController.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACJumpScareEnemy::ACJumpScareEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CatchCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CatchCameraArm"));
	CatchCameraArm->SetupAttachment(RootComponent);
	CatchCameraArm->TargetArmLength = 350.f;
	CatchCameraArm->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CatchCameraArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	CatchCameraArm->bDoCollisionTest = false;
	
	CatchCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CatchCamera"));
	CatchCamera->SetupAttachment(CatchCameraArm);

}

// Called when the game starts or when spawned
void ACJumpScareEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CachedPlayer = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	CachedPC = CachedPlayer ? Cast<ACPlayerController>(CachedPlayer->GetController()) : nullptr;
	
}

// Called every frame
void ACJumpScareEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForCatch();
}

void ACJumpScareEnemy::CheckForCatch()
{
	if (bHasCaughtPlayer || !CachedPlayer || !CachedPC) return;

	const float DistSquared = FVector::DistSquared(GetActorLocation(), CachedPlayer->GetActorLocation());
	if (DistSquared > FMath::Square(CatchRadius)) return;

	bHasCaughtPlayer = true;

	// Stops this enemy's own movement
	if (AAIController* AICon = Cast<AAIController>(GetController()))
	{
		if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(AICon->GetBrainComponent()))
		{
			BTComp->StopTree(EBTStopMode::Forced);
		}
		AICon->StopMovement();
	}

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->DisableMovement();
	}

	TriggerCatchSequence();
}

void ACJumpScareEnemy::TriggerCatchSequence()
{
	
	// Stops the player's movement/input
	if (UCharacterMovementComponent* MoveComponent = CachedPlayer->GetCharacterMovement())
	{
		MoveComponent->DisableMovement();
	}
	CachedPC->SetIgnoreMoveInput(true);
	CachedPC->SetIgnoreLookInput(true);
	
	// Pulls the camera out and into the enemy's kill cam
	CachedPC->SetViewTargetWithBlend(this, CameraBlendTime);
	
	// Wait for the camera blend before playing the animation
	GetWorld()->GetTimerManager().SetTimer(CatchAnimTimerHandle, this, 
		&ACJumpScareEnemy::PlayHitMontage, AnimationDelay, false);
	
}

void ACJumpScareEnemy::PlayHitMontage()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayHitMontage called. HitMontages count: %d"), HitMontages.Num());
	
	if (HitMontages.Num() == 0) return;
	
	const int32 RandomIndex = FMath::RandRange(0, HitMontages.Num() - 1);
	UAnimMontage* ChosenMontage = HitMontages[RandomIndex];
	if (!ChosenMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;
	
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ACJumpScareEnemy::OnHitMontageEnded);
	AnimInstance->Montage_Play(ChosenMontage);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ChosenMontage);
}

void ACJumpScareEnemy::OnHitMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (CachedPC)
	{
		CachedPC->ShowGameOverSequence();
	}
}

