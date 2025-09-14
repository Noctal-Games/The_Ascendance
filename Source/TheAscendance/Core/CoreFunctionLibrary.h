// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CoreFunctionLibrary.generated.h"

class APlayableGameMode;
class APlayerCharacter;
class ATAPlayerController;

UCLASS()
class THEASCENDANCE_API UCoreFunctionLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Core")
	static UWorld* GetGameWorld();

	UFUNCTION(BlueprintCallable, Category = "Core")
	static APlayableGameMode* GetPlayableGameMode();

	UFUNCTION(BlueprintCallable, Category = "Core")
	static APlayerCharacter* GetPlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "Core")
	static ATAPlayerController* GetPlayerController();

	//C++ Only
	//static UDataHandlerSubsystem* GetDataHandlerSubsystem();
	static void RequestAsyncLoad(const FSoftObjectPath& targetToStream, TFunction<void()> delegate = nullptr);
};
