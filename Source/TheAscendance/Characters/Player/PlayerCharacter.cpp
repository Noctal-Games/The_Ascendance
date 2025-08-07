// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerMovementComponent.h"
#include "TheAscendance/Characters/Components/CharacterStatsComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : ABaseCharacter()
{
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	checkf(_camera, TEXT("Player Camera failed to initialise"));
	_camera->SetupAttachment(GetRootComponent());
	_camera->bUsePawnControlRotation = true;
}

void APlayerCharacter::SetPlayerController(ATAPlayerController* PlayerController)
{
	_playerController = PlayerController;
}

ATAPlayerController* APlayerCharacter::GetPlayerController()
{
	return _playerController;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	ABaseCharacter::Tick(DeltaTime);
}

void APlayerCharacter::SetIsSprinting(bool val)
{
	_isSprinting = val;
}
bool APlayerCharacter::IsSprinting()
{
	if (characterStatsComponent->GetStatAsValue(ECharacterStat::STAMINA) <= 0)
	{
		return false;
	}

	return _isSprinting;
}
void APlayerCharacter::SetIsCrouching(bool val)
{
	_isCrouching = val;
}
bool APlayerCharacter::IsCrouching()
{
	if (_isJumping == true)
	{
		return false;
	}

	return _isCrouching;
}
bool APlayerCharacter::IsCrouched()
{
	return _currentCapsuleHeight < _defaultCapsuleHeight - 5;
}
void APlayerCharacter::SetIsJumping()
{
	_isJumping = true;
}
bool APlayerCharacter::CanJumpInternal_Implementation() const
{
	if (bIsCrouched == true || characterStatsComponent->GetStatAsValue(ECharacterStat::STAMINA) < 5)
	{
		return false;
	}

	if (JumpIsAllowedInternal() == false)
	{
		if (_movementComponent->IsSprinting() == true)
		{
			return true;
		}

		return false;
	}

	return true;
}
void APlayerCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	characterStatsComponent->AdjustStatByValue(ECharacterStat::STAMINA, -5);
}
float APlayerCharacter::GetDefaultCapsuleHeight()
{
	return _defaultCapsuleHeight;
}
void APlayerCharacter::UpdateCrouchCamera(float DeltaTime)
{
	float crouchSpeed = DeltaTime * 5;

	if (_movementComponent->IsCrouchingCustom() && _currentCapsuleHeight > _crouchCapsuleHeight)
	{
		_currentCapsuleHeight = FMath::Lerp(_currentCapsuleHeight, _crouchCapsuleHeight, crouchSpeed);
		GetCapsuleComponent()->SetCapsuleSize(_defaultCapsuleRadius, _currentCapsuleHeight, true);
	}
	if (_movementComponent->IsCrouchingCustom() == false && _currentCapsuleHeight < _defaultCapsuleHeight)
	{
		_currentCapsuleHeight = FMath::Lerp(_currentCapsuleHeight, _defaultCapsuleHeight, crouchSpeed);
		GetCapsuleComponent()->SetCapsuleSize(_defaultCapsuleRadius, _currentCapsuleHeight, true);
	}
}
void APlayerCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (PrevMovementMode != EMovementMode::MOVE_Falling)
	{
		return;
	}

	_isJumping = false;
}

UCameraComponent* APlayerCharacter::GetCamera()
{
	return _camera;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	_movementComponent = Cast<UPlayerMovementComponent>(GetMovementComponent());
	checkf(_movementComponent, TEXT("Movement Component is an invalid value"));

	_defaultCapsuleRadius = GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	_defaultCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	_currentCapsuleHeight = _defaultCapsuleHeight;
	_crouchCapsuleHeight = _defaultCapsuleHeight / 2;

	if (characterStatsComponent != nullptr)
	{
		characterStatsComponent->AddStat(ECharacterStat::HEALTH, _baseHealth);
		characterStatsComponent->AddStat(ECharacterStat::STAMINA, _baseStamina);
		characterStatsComponent->AddStat(ECharacterStat::MANA, _baseMana);
		characterStatsComponent->AddStat(ECharacterStat::SPEED, _baseSpeed);
		characterStatsComponent->AddStat(ECharacterStat::PHYSICAL_ATTACK, 0);
		characterStatsComponent->AddStat(ECharacterStat::PHYSICAL_RESISTANCE, 0);
		characterStatsComponent->AddStat(ECharacterStat::MAGIC_ATTACK, 0);
		characterStatsComponent->AddStat(ECharacterStat::MAGIC_RESISTANCE, 0);
	}
}



