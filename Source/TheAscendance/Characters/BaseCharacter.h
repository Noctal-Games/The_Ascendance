// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Susceptible.h"
#include "Enums/CharacterStat.h"
#include "BaseCharacter.generated.h"

class UCharacterStatsComponent;

UCLASS()
class THEASCENDANCE_API ABaseCharacter : public ACharacter, public ISusceptible
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void Heal(int amount) override;
	virtual void Damage(int amount) override;
	virtual void ReduceStamina(int amount) override;
	virtual int GetStat(ECharacterStat stat) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Character Stats Component"))
	TObjectPtr<UCharacterStatsComponent> m_CharacterStatsComponent = nullptr;
};
