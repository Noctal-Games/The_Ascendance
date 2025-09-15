// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreFunctionLibrary.h"
#include "TheAscendance/Characters/Player/PlayerCharacter.h"
#include "TheAscendance/Characters/Player/TAPlayerController.h"
#include "TheAscendance/Game/GameModes/PlayableGameMode.h"
#include "TheAscendance/Game/Subsystems/DataHandlerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UWorld* UCoreFunctionLibrary::GetGameWorld()
{
	return GEngine->GameViewport->GetWorld();
}

APlayableGameMode* UCoreFunctionLibrary::GetPlayableGameMode()
{
	if (UWorld* world = GetGameWorld())
	{
		return world->GetAuthGameMode<APlayableGameMode>();
	}

	return nullptr;
}

APlayerCharacter* UCoreFunctionLibrary::GetPlayerCharacter()
{
	if (APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetGameWorld(), 0)))
	{
		return player;
	}

	return nullptr;
}

ATAPlayerController* UCoreFunctionLibrary::GetPlayerController()
{
	if (ATAPlayerController* controller = Cast<ATAPlayerController>(UGameplayStatics::GetPlayerController(GetGameWorld(), 0)))
	{
		return controller;
	}

	return nullptr;
}

UDataHandlerSubsystem* UCoreFunctionLibrary::GetDataHandlerSubsystem()
{
	if (UWorld* world = GetGameWorld())
	{
		return world->GetGameInstance()->GetSubsystem<UDataHandlerSubsystem>();
	}

	return nullptr;
}

void UCoreFunctionLibrary::RequestAsyncLoad(const FSoftObjectPath& targetToStream, TFunction<void()> delegate)
{
	if (delegate == nullptr)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(targetToStream);
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(targetToStream, FStreamableDelegate::CreateLambda(delegate));
}
