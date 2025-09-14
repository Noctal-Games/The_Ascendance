// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheAscendance/Items/Containers/Structs/InventorySlotData.h"
#include <memory>
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEASCENDANCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void SetInventory(const TArray<FInventorySlotData>& inventory);
	void AddItem(int id, int amount);

	void RemoveItem(int id, int amount);
	void RemoveItemAtIndex(int index, int amount);

	int GetItemCount(int id);
	const TArray<FInventorySlotData>& GetInventory();

	std::shared_ptr<FInventorySlotData> GetInventorySlotDataAtIndex(int index);

	bool Contains(int id);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	std::shared_ptr<FInventorySlotData> GetInventorySlotData(int id);
	void RemoveItemFromArray(int index);

private:
	TArray<FInventorySlotData> m_Inventory;
};
