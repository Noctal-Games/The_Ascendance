// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterStat : uint8
{
	NONE UMETA(DisplayName = "None"),
	HEALTH UMETA(DisplayName = "Health"),
	STAMINA UMETA(DisplayName = "Stamina"),
	MANA UMETA(DisplayName = "Mana"),
	SPEED UMETA(DisplayName = "Speed"),
	PHYSICAL_ATTACK UMETA(DisplayName = "Physical Attack (%)"),
	MAGIC_ATTACK UMETA(DisplayName = "Magic Attack (%)"),
	PHYSICAL_RESISTANCE UMETA(DisplayName = "Physical Resistance (%)"),
	MAGIC_RESISTANCE UMETA(DisplayName = "Magic Resistance (%)")
};
