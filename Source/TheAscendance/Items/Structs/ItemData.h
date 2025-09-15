// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Items/Enums/ItemType.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int ItemID = 0;
	UPROPERTY(EditAnywhere)
	FName ItemName = "";
	UPROPERTY(EditAnywhere)
	EItemType ItemType = EItemType::DEFAULT;
	UPROPERTY(EditAnywhere)
	FString ItemDescription = "";
	UPROPERTY(EditAnywhere)
	bool IsStackable = true;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> ItemMesh = nullptr;

	FItemData() {}

	FItemData(FItemData& itemData)
	{
		ItemID = itemData.ItemID;
		ItemName = itemData.ItemName;
		ItemType = itemData.ItemType;
		ItemDescription = itemData.ItemDescription;
		IsStackable = itemData.IsStackable;
		ItemMesh = itemData.ItemMesh;
	}
};

