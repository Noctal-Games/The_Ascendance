// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheAscendance/Characters/Enums/CharacterStat.h"
#include "CharacterStatsComponent.generated.h"

DECLARE_DELEGATE_TwoParams(FOnStatChanged, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEASCENDANCE_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

	void AddStat(ECharacterStat stat, float maxValue);

	void AdjustStatByValue(ECharacterStat stat, float amount);
	void AdjustStatByPercentage(ECharacterStat stat, float percentage);
	void AdjustMaxStatByValue(ECharacterStat stat, int amount);
	void SetStat(ECharacterStat stat, float amount);

	int GetStatAsValue(ECharacterStat stat) const;
	int GetStatAsPercentage(ECharacterStat stat) const;
	int GetStatBaseValue(ECharacterStat stat) const;
	int GetStatMaxValue(ECharacterStat stat) const;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ExecuteBindings(ECharacterStat stat);

	void LogStatWarning(ECharacterStat stat);
	void LogStatError(ECharacterStat stat);

public:
	FOnStatChanged OnStaminaChanged;
	FOnStatChanged OnHealthChanged;
	FOnStatChanged OnManaChanged;
	FOnStatChanged OnSpeedChanged;

private:
	UPROPERTY()
	TMap<ECharacterStat, float> _statsBase;
	UPROPERTY()
	TMap<ECharacterStat, int> _statsMax;
	UPROPERTY()
	TMap<ECharacterStat, float> _stats;

	//--- STAMINA ----
	UPROPERTY(EditDefaultsOnly, Category = "STATS | STAMINA")
	float _staminaRegenPerTick;
	UPROPERTY(EditDefaultsOnly, Category = "STATS | STAMINA")
	float _staminaRegenDelay;
	float _staminaTimer;

	//--- MANA ----
	UPROPERTY(EditDefaultsOnly, Category = "STATS | MANA")
	float _manaRegenPerTick;
	UPROPERTY(EditDefaultsOnly, Category = "STATS | MANA")
	float _manaRegenDelay;
	float _manaTimer;
};
