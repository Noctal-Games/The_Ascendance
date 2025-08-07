// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerMovementComponent;
class UCameraComponent;
class ATAPlayerController;

UCLASS()
class THEASCENDANCE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void SetPlayerController(ATAPlayerController* PlayerController);
	ATAPlayerController* GetPlayerController();

	void SetIsSprinting(bool val);
	bool IsSprinting();
	void SetIsCrouching(bool val);
	bool IsCrouching();
	bool IsCrouched();
	void SetIsJumping();
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void OnJumped_Implementation() override;
	float GetDefaultCapsuleHeight();

	void UpdateCrouchCamera(float DeltaTime);
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	UCameraComponent* GetCamera();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CAMERA")
	TObjectPtr<UCameraComponent> _camera;
	UPROPERTY(EditDefaultsOnly, Category = "MOVEMENT")
	TObjectPtr<UPlayerMovementComponent> _movementComponent;
	UPROPERTY()
	TObjectPtr<ATAPlayerController> _playerController;

	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseHealth;
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseStamina;
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseMana;
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseSpeed;

	float _crouchCapsuleHeight;
	float _currentCapsuleHeight;
	float _defaultCapsuleHeight;
	float _defaultCapsuleRadius;

	bool _isSprinting;
	bool _isCrouching;
	bool _isJumping;
};
