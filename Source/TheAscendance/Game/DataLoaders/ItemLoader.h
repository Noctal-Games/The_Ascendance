// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemLoader.generated.h"

struct FItemData;

UCLASS()
class THEASCENDANCE_API UItemLoader : public UObject
{
	GENERATED_BODY()

public:
	void Init();

	FItemData* GetItemData(int itemID);
private:
	UPROPERTY()
	TObjectPtr<UDataTable> m_ItemTable;
};
