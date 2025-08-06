// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "TheAscendance/Characters/Components/CharacterStatsComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : ABaseCharacter()
{
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	ABaseCharacter::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	if (characterStatsComponent != nullptr)
	{
		characterStatsComponent->AddStat(ECharacterStat::HEALTH, _baseHealth);
		characterStatsComponent->AddStat(ECharacterStat::STAMINA, _baseStamina);
		characterStatsComponent->AddStat(ECharacterStat::MANA, _baseMana);
		characterStatsComponent->AddStat(ECharacterStat::SPEED, _baseSpeed);
		characterStatsComponent->AddStat(ECharacterStat::PHYSICAL_ATTACK, 0);
		characterStatsComponent->AddStat(ECharacterStat::PHYSICAL_RESISTANCE, 0);
		characterStatsComponent->AddStat(ECharacterStat::MAGIC_ATTACK, 0);
		characterStatsComponent->AddStat(ECharacterStat::MAGIC_RESISTANCE, 0);
	}
}



