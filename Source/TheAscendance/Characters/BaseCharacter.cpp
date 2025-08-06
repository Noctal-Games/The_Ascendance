// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CharacterStatsComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseCharacter::Heal(int amount)
{
	if (characterStatsComponent == nullptr)
	{
		return;
	}

	characterStatsComponent->AdjustStatByValue(ECharacterStat::HEALTH, amount);
}

void ABaseCharacter::Damage(int amount)
{
	if (characterStatsComponent == nullptr)
	{
		return;
	}

	characterStatsComponent->AdjustStatByValue(ECharacterStat::HEALTH, -amount);
}

void ABaseCharacter::ReduceStamina(int amount)
{
	if (characterStatsComponent == nullptr)
	{
		return;
	}

	characterStatsComponent->AdjustStatByValue(ECharacterStat::STAMINA, -amount);
}

int ABaseCharacter::GetStat(ECharacterStat stat)
{
	if (characterStatsComponent == nullptr)
	{
		return 0;
	}

	return characterStatsComponent->GetStatAsValue(stat);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}



