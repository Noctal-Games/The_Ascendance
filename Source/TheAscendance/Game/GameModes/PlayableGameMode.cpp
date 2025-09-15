// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableGameMode.h"
#include "TheAscendance/Game/DataLoaders/ItemLoader.h"
#include "TheAscendance/Core/CoreMacros.h"

FItemData* APlayableGameMode::GetItemData(int id)
{
	if (m_ItemLoader == nullptr)
	{
		return nullptr;
	}

	return m_ItemLoader->GetItemData(id);
}

void APlayableGameMode::StartPlay()
{
	if (m_ItemLoader = NewObject<UItemLoader>())
	{
		m_ItemLoader->Init();
	}
	else
	{
		LOG_ERROR("PlayableGameMode failed to create ItemLoader");
	}

	Super::StartPlay();
}

void APlayableGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APlayableGameMode::StartToLeaveMap()
{
	// Save Logic
	Super::StartToLeaveMap();
}


