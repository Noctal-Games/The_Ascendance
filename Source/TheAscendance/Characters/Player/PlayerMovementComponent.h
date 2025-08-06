// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMovementComponent.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None UMETA(DisplayName = "None"),
	CMOVE_Sprinting UMETA(DisplayName = "Sprinting"),
	CMOVE_Crouching UMETA(DisplayName = "Crouching"),
	CMOVE_SprintCrouch UMETA(DisplayName = "SprintCrouching"),
	CMOVE_MAX UMETA(Hidden),
};

class APlayerCharacter;

UCLASS()
class THEASCENDANCE_API UPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void UpdateCharacterStateAfterMovement(float DeltaSeconds) override;

	void TrySprinting();
	bool CanSprint();
	void PhysSprinting(float DeltaTime, int32 Iterations);

	void TryCrouching();
	bool CanCrouch();
	void PhysCrouching(float DeltaTime, int32 Iterations);
	bool CanUnCrouch();

	UFUNCTION(BlueprintPure)
	float GetSpeed() const;
	UFUNCTION(BlueprintPure)
	bool IsWalkingCustom() const;
	UFUNCTION(BlueprintPure)
	bool IsSprinting() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCrouchingCustom() const;
	bool IsCustomMovementMode() const;
	float GetCapsuleRadius() const;
	float GetCapsuleHalfHeight() const;
	virtual float GetMaxSpeed() const override;

protected:
	virtual void InitializeComponent() override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

private:
	//---- MANTLING ----
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	float _maxFrontMantleCheckDistance = 50;
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	float _mantleUpOffsetDistance = 30;
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	float _mantleReachHeight = 50;
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	float _mantleMinWallSteepnessAngle = 75;
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	float _mantleMaxSurfaceAngle = 40;
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	float _mantleMaxAlignmentAngle = 55;

	//---- SPRINTING ----
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Sprinting")
	float _sprintSpeedBonus = 200.f;
	bool _isSprinting;

	//---- CROUCHING ----
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Crouching")
	float _crouchSpeed = 200.0f;
	bool _isCrouching;

	TWeakObjectPtr<APlayerCharacter> _player;

	EMovementMode _lastMode;
};
