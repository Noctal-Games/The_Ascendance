// Fill out your copyright notice in the Description page of Project Settings.
#include "TAPlayerController.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ATAPlayerController::DisplayHUD()
{
}

void ATAPlayerController::HandleLook(const FInputActionValue& Value)
{
	const FVector rotationVector = Value.Get<FVector>();

	AddYawInput(rotationVector.X * horizontalSensitivity);
	AddPitchInput(rotationVector.Y * verticalSensitivity);
}

void ATAPlayerController::HandleMove(const FInputActionValue& Value)
{
	const FVector movementVector = Value.Get<FVector>();

	_playerCharacter->AddMovementInput(_playerCharacter->GetActorForwardVector(), movementVector.Y);
	_playerCharacter->AddMovementInput(_playerCharacter->GetCamera()->GetRightVector(), movementVector.X);
}

void ATAPlayerController::HandleJump()
{
	_playerCharacter->SetIsJumping();
	_playerCharacter->Jump();
}

void ATAPlayerController::HandleStartSprint()
{
	_playerCharacter->SetIsSprinting(true);
}

void ATAPlayerController::HandleEndSprint()
{
	_playerCharacter->SetIsSprinting(false);
}

void ATAPlayerController::HandleStartCrouch()
{
	_playerCharacter->SetIsCrouching(true);
}

void ATAPlayerController::HandleEndCrouch()
{
	_playerCharacter->SetIsCrouching(false);
}

void ATAPlayerController::HandleMainHandPrimaryAttack()
{
}

void ATAPlayerController::HandleMainHandAltAttack()
{
}

void ATAPlayerController::HandleOffhandPrimaryAttack()
{
}

void ATAPlayerController::HandleOffhandAltAttack()
{
}

void ATAPlayerController::HandleToggleInventory()
{
}

void ATAPlayerController::HandleToggleQuestMenu()
{
}

void ATAPlayerController::HandleTogglePauseMenu()
{
}

void ATAPlayerController::HandleInteract()
{
}

void ATAPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	//if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	//{
	//	_uiManager = uiManager;
	//	_uiManager->CreateWidgets(this);
	//}

	_playerCharacter = Cast<APlayerCharacter>(aPawn);
	_playerCharacter->SetPlayerController(this);

	_enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(_enhancedInputComponent, TEXT("ENHANCED_INPUT_COMPONENT is an invalid value"));

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("INPUT_SUBSYSTEM is an invalid value"));

	checkf(inputMappingContext, TEXT("INPUT_MAPPING_CONTEXT is an invalid value"));
	inputSubsystem->ClearAllMappings();
	inputSubsystem->AddMappingContext(inputMappingContext, 0);

	BindActions(_enhancedInputComponent);
}

void ATAPlayerController::OnUnPossess()
{
	_enhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void ATAPlayerController::BindActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	checkf(actionLook, TEXT("Missing 'Look' Action"));
	EnhancedInputComponent->BindAction(actionLook, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleLook);

	checkf(actionMove, TEXT("Missing 'Move' Action"));
	EnhancedInputComponent->BindAction(actionMove, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMove);

	checkf(actionJump, TEXT("Missing 'Jump' Action"));
	EnhancedInputComponent->BindAction(actionJump, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleJump);

	checkf(actionSprint, TEXT("Missing 'Sprint' Action"));
	EnhancedInputComponent->BindAction(actionSprint, ETriggerEvent::Started, this, &ATAPlayerController::HandleStartSprint);
	EnhancedInputComponent->BindAction(actionSprint, ETriggerEvent::Completed, this, &ATAPlayerController::HandleEndSprint);

	checkf(actionSprint, TEXT("Missing 'Crouch' Action"));
	EnhancedInputComponent->BindAction(actionCrouch, ETriggerEvent::Started, this, &ATAPlayerController::HandleStartCrouch);
	EnhancedInputComponent->BindAction(actionCrouch, ETriggerEvent::Completed, this, &ATAPlayerController::HandleEndCrouch);

	checkf(actionToggleInventory, TEXT("Missing 'Toggle Inventory' Action"));
	EnhancedInputComponent->BindAction(actionToggleInventory, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleToggleInventory);

	checkf(actionToggleQuestMenu, TEXT("Missing 'Toggle Quest Menu' Action"));
	EnhancedInputComponent->BindAction(actionToggleQuestMenu, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleToggleQuestMenu);

	checkf(actionMainHandPrimaryAttack, TEXT("Missing 'Main Hand Primary Attack' Action"));
	EnhancedInputComponent->BindAction(actionMainHandPrimaryAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMainHandPrimaryAttack);
	checkf(actionMainHandAltAttack, TEXT("Missing 'Main Hand Alt Attack' Action"));
	EnhancedInputComponent->BindAction(actionMainHandAltAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMainHandAltAttack);

	checkf(actionOffhandPrimaryAttack, TEXT("Missing 'Offhand Primary Attack' Action"));
	EnhancedInputComponent->BindAction(actionOffhandPrimaryAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleOffhandPrimaryAttack);
	checkf(actionOffhandAltAttack, TEXT("Missing 'Offhand Alt Attack' Action"));
	EnhancedInputComponent->BindAction(actionOffhandAltAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleOffhandAltAttack);

	checkf(actionTogglePauseMenu, TEXT("Missing 'TogglePauseMenu' Action"));
	EnhancedInputComponent->BindAction(actionTogglePauseMenu, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTogglePauseMenu);

	checkf(actionInteract, TEXT("Missing 'Interact' Action"));
	EnhancedInputComponent->BindAction(actionInteract, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleInteract);
}
