// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

void UPlayerMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	TrySprinting();
	TryCrouching();

	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

void UPlayerMovementComponent::UpdateCharacterStateAfterMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateAfterMovement(DeltaSeconds);
}

void UPlayerMovementComponent::TrySprinting()
{
	_isSprinting = CanSprint();

	if (_isSprinting == false)
	{
		return;
	}

	if (_isCrouching == true)
	{
		SetMovementMode(MOVE_Custom, CMOVE_SprintCrouch);
	}
	else
	{
		SetMovementMode(MOVE_Custom, CMOVE_Sprinting);
	}
}

bool UPlayerMovementComponent::CanSprint()
{
	if (IsFalling() == true || _player->IsSprinting() == false)
	{
		return false;
	}

	FVector direction = Velocity;
	direction.Normalize();

	if (FVector::DotProduct(_player->GetActorForwardVector(), direction) <= 0.1)
	{
		return false;
	}

	// Check if the character is on walkable floor
	FFindFloorResult floorResult;
	FindFloor(UpdatedComponent->GetComponentLocation(), floorResult, false);

	return floorResult.bWalkableFloor;
}

void UPlayerMovementComponent::PhysSprinting(float DeltaTime, int32 Iterations)
{
	if (_isSprinting == false)
	{
		// Restore default walk variables
		SetMovementMode(DefaultLandMovementMode);
	}

	PhysWalking(DeltaTime, Iterations);
}

void UPlayerMovementComponent::TryCrouching()
{
	_isCrouching = CanCrouch();

	if (_isCrouching == false)
	{
		return;
	}

	if (_isSprinting == true)
	{
		SetMovementMode(MOVE_Custom, CMOVE_SprintCrouch);
	}
	else
	{
		SetMovementMode(MOVE_Custom, CMOVE_Crouching);
	}
}
bool UPlayerMovementComponent::CanCrouch()
{
	if (IsFalling() == true || (_player->IsCrouching() == false && (_player->IsCrouched() == false || _player->IsCrouched() == true && CanUnCrouch() == true)))
	{
		return false;
	}

	// Check if the character is on walkable floor
	FFindFloorResult floorResult;
	FindFloor(UpdatedComponent->GetComponentLocation(), floorResult, false);

	return floorResult.bWalkableFloor;
}

void UPlayerMovementComponent::PhysCrouching(float DeltaTime, int32 Iterations)
{
	if (_isCrouching == false)
	{
		// Restore default walk variables
		SetMovementMode(DefaultLandMovementMode);
	}

	PhysWalking(DeltaTime, Iterations);
}

bool UPlayerMovementComponent::CanUnCrouch()
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());

	FVector transitionTarget = GetActorLocation();
	transitionTarget.Z += _player->GetDefaultCapsuleHeight();

	FCollisionShape capShape = FCollisionShape::MakeCapsule(GetCapsuleRadius(), GetCapsuleHalfHeight());

	//DrawDebugCapsule(GetWorld(), transitionTarget, GetCapsuleHalfHeight(), GetCapsuleRadius(), FQuat::Identity, FColor::Green, false, 3);

	if (GetWorld()->OverlapAnyTestByProfile(transitionTarget, FQuat::Identity, "BlockAll", capShape, params) == true)
	{
		return false;
	}

	return true;
}

float UPlayerMovementComponent::GetSpeed() 
{
	return Velocity.Length();
}

bool UPlayerMovementComponent::IsWalkingCustom() 
{
	if (!IsWalking() || FMath::IsNearlyZero(GetSpeed()))
	{
		return false;
	}

	if (IsSprinting())
	{
		return false;
	}

	return true;
}

bool UPlayerMovementComponent::IsSprinting() 
{
	return _isSprinting;
}
bool UPlayerMovementComponent::IsCrouchingCustom() 
{
	return _isCrouching;
}

bool UPlayerMovementComponent::IsCustomMovementMode() 
{
	return MovementMode == MOVE_Custom;
}
float UPlayerMovementComponent::GetCapsuleRadius() 
{
	return CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
}
float UPlayerMovementComponent::GetCapsuleHalfHeight() 
{
	return CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}
float UPlayerMovementComponent::GetMaxSpeed() const
{
	const float maxSpeed = Super::GetMaxSpeed();

	if (MovementMode != MOVE_Custom)
	{
		return maxSpeed;
	}

	switch (CustomMovementMode)
	{
	case CMOVE_Sprinting:
		return  maxSpeed * 1.3;
	case CMOVE_Crouching:
		return _crouchSpeed;
	case CMOVE_SprintCrouch:
		return _crouchSpeed + (_sprintSpeedBonus / 2);
	default:
		return maxSpeed;
	}
}
void UPlayerMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	_player = Cast<APlayerCharacter>(GetOwner());

	_lastMode = EMovementMode::MOVE_Walking;
}

void UPlayerMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	switch (CustomMovementMode)
	{
	case CMOVE_Sprinting:
		PhysSprinting(deltaTime, Iterations);
		break;
	case CMOVE_Crouching:
		PhysCrouching(deltaTime, Iterations);
		break;
	case CMOVE_SprintCrouch:
		PhysCrouching(deltaTime, Iterations);
		break;
	}
}