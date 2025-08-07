// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TAPlayerController.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class UInputAction;
class UCharacterMovementComponent;
class APlayerCharacter;

UCLASS()
class THEASCENDANCE_API ATAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void DisplayHUD();

protected:
	//---- INPUT HANDLERS ----
	void HandleLook(const struct FInputActionValue& Value);
	void HandleMove(const struct FInputActionValue& Value);
	void HandleJump();
	void HandleStartSprint();
	void HandleEndSprint();
	void HandleStartCrouch();
	void HandleEndCrouch();

	void HandleMainHandPrimaryAttack();
	void HandleMainHandAltAttack();

	void HandleOffhandPrimaryAttack();
	void HandleOffhandAltAttack();

	void HandleToggleInventory();
	void HandleToggleQuestMenu();
	void HandleTogglePauseMenu();
	void HandleInteract();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
private:
	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);

public:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float horizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float verticalSensitivity;

	//---- INPUTS ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Mapping Context")
	TObjectPtr<UInputMappingContext> inputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> actionLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> actionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> actionJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> actionSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> actionCrouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionToggleInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionToggleQuestMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionMainHandPrimaryAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionMainHandAltAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionOffhandPrimaryAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionOffhandAltAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionTogglePauseMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> actionInteract;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> _enhancedInputComponent;
	UPROPERTY()
	TWeakObjectPtr<APlayerCharacter> _playerCharacter;
};
