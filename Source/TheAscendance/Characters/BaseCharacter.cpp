// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CharacterStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CharacterStatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Character Stats Component"));
	checkf(m_CharacterStatsComponent, TEXT("Character Stats Component failed to initialise"));
}

void ABaseCharacter::Heal(int amount)
{
	if (m_CharacterStatsComponent == nullptr)
	{
		return;
	}

	m_CharacterStatsComponent->AdjustStatByValue(ECharacterStat::HEALTH, amount);
}

void ABaseCharacter::Damage(int amount)
{
	if (m_CharacterStatsComponent == nullptr)
	{
		return;
	}

	m_CharacterStatsComponent->AdjustStatByValue(ECharacterStat::HEALTH, -amount);
}

void ABaseCharacter::ReduceStamina(int amount)
{
	if (m_CharacterStatsComponent == nullptr)
	{
		return;
	}

	m_CharacterStatsComponent->AdjustStatByValue(ECharacterStat::STAMINA, -amount);
}

int ABaseCharacter::GetStat(ECharacterStat stat)
{
	if (m_CharacterStatsComponent == nullptr)
	{
		return 0;
	}

	return m_CharacterStatsComponent->GetStatAsValue(stat);
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

	m_CharacterStatsComponent->OnSpeedChanged.BindLambda([this](float walkSpeed) { GetCharacterMovement()->MaxWalkSpeed = walkSpeed; });
	m_CharacterStatsComponent->Init();
}



