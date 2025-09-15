// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLoader.h"
#include "TheAscendance/Core/CoreFunctionLibrary.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "TheAscendance/Game/Subsystems/DataHandlerSubsystem.h"
#include "TheAscendance/Items/Structs/ItemData.h"

void UItemLoader::Init()
{
	if (UDataHandlerSubsystem* dataHandler = UCoreFunctionLibrary::GetDataHandlerSubsystem())
	{
		 m_ItemTable = dataHandler->LoadData(EDataGroup::ITEMS);

		if (m_ItemTable == nullptr)
		{
			LOG_ERROR("ItemLoader failed to load Item DataTable");
		}
	}
}

FItemData* UItemLoader::GetItemData(int itemID)
{
	if (m_ItemTable == nullptr)
	{
		LOG_ERROR("ItemLoader tried to load ItemData without a valid ItemTable");
		return nullptr;
	}

	static const FString contextString(TEXT("Item Context String"));

	TArray<FItemData*> itemStructs;
	m_ItemTable->GetAllRows(contextString, itemStructs);

	for (const auto data : itemStructs)
	{
		if (data->ItemID == itemID)
		{
			return data;
		}
	}

	LOG_ERROR("ItemLoader could not load ItemData for Item ID: %i", itemID);
	return nullptr;
}
