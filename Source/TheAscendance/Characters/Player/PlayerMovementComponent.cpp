// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"

void UPlayerMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconda)
{
}

void UPlayerMovementComponent::UpdateCharacterStateAfterMovement(float DeltaSeconda)
{
}

void UPlayerMovementComponent::TrySprinting()
{
}

bool UPlayerMovementComponent::CanSprint()
{
	return false;
}

void UPlayerMovementComponent::PhysSprinting(float DeltaTime, int32 Iterations)
{
}

void UPlayerMovementComponent::TryCrouching()
{
}
bool UPlayerMovementComponent::CanCrouch()
{
	return false;
}

void UPlayerMovementComponent::PhysCrouching(float DeltaTime, int32 Iterations)
{
}

bool UPlayerMovementComponent::CanUnCrouch()
{
	return false;
}

void UPlayerMovementComponent::InitializeComponent()
{
}

void UPlayerMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
}

float UPlayerMovementComponent::GetSpeed() const
{
	return 0.0f;
}

bool UPlayerMovementComponent::IsWalkingCustom() const
{
	return true;
}
bool UPlayerMovementComponent::IsSprinting() const
{
	return true;
}
bool UPlayerMovementComponent::IsCrouchingCustom() const
{
	return true;
}

bool UPlayerMovementComponent::IsCustomMovementMode() const
{
	return false;
}
