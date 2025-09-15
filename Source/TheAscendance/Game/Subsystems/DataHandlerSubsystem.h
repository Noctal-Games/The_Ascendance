// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataHandlerSubsystem.generated.h"

UENUM()
enum class EDataGroup : uint8
{
	ENEMIES,
	ITEMS,
	SPELLS,
	EFFECTS
};

UCLASS(Blueprintable)
class THEASCENDANCE_API UDataHandlerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UDataTable* LoadData(EDataGroup dataGroup);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Data Tables"))
	TMap<EDataGroup, TSoftObjectPtr<UDataTable>> m_DataTables;
};
