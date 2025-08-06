// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatsComponent.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCharacterStatsComponent::AddStat(ECharacterStat stat, float maxValue)
{
	if (_statsBase.Contains(stat) == true)
	{
		_statsBase[stat] = maxValue;
	}
	else
	{
		_statsBase.Add(stat, maxValue);
	}

	if (_statsMax.Contains(stat) == true)
	{
		_statsMax[stat] = maxValue;
	}
	else
	{
		_statsMax.Add(stat, maxValue);
	}

	if (_stats.Contains(stat) == true)
	{
		_stats[stat] = maxValue;
	}
	else
	{
		_stats.Add(stat, maxValue);
	}

	AdjustStatByValue(stat, 0);

	if (stat != ECharacterStat::HEALTH && stat != ECharacterStat::STAMINA && stat != ECharacterStat::MANA && stat != ECharacterStat::SPEED)
	{
		return;
	}

	ExecuteBindings(stat);
}

void UCharacterStatsComponent::AdjustStatByValue(ECharacterStat stat, float amount)
{
	if (_stats.Contains(stat) == false)
	{
		LogStatError(stat);
		return;
	}

	if (stat != ECharacterStat::HEALTH && stat != ECharacterStat::STAMINA && stat != ECharacterStat::MANA)
	{
		_stats[stat] += amount;

		if (_stats[stat] < 0)
		{
			_stats[stat] = 0;
		}

		if (stat == ECharacterStat::SPEED)
		{
			ExecuteBindings(stat);
		}

		return;
	}

	_stats[stat] = FMath::Clamp(_stats[stat] += amount, 0, _statsMax[stat]);

	ExecuteBindings(stat);

	if (stat == ECharacterStat::STAMINA)
	{
		_staminaTimer = _staminaRegenDelay;
	}
	else if (stat == ECharacterStat::MANA)
	{
		_manaTimer = _manaRegenDelay;
	}
}

void UCharacterStatsComponent::AdjustStatByPercentage(ECharacterStat stat, float percentage)
{
	if (_stats.Contains(stat) == false)
	{
		LogStatError(stat);
		return;
	}

	float adjust = _statsBase[stat];

	//If percentage is negative, then get it's absolute multiplier and negate it from health. Else, add the multiplier to health.
	if (percentage < 0)
	{
		adjust *= (FMath::Abs(percentage) / 100);
		_stats[stat] -= FMath::FloorToInt(adjust);
	}
	else
	{
		adjust *= percentage / 100;
		_stats[stat] += FMath::FloorToInt(adjust);
	}

	if (stat != ECharacterStat::HEALTH && stat != ECharacterStat::STAMINA && stat != ECharacterStat::MANA && stat != ECharacterStat::SPEED)
	{
		return;
	}

	ExecuteBindings(stat);

	if (stat == ECharacterStat::STAMINA)
	{
		_staminaTimer = _staminaRegenDelay;
	}
	else if (stat == ECharacterStat::MANA)
	{
		_manaTimer = _manaRegenDelay;
	}
}

void UCharacterStatsComponent::AdjustMaxStatByValue(ECharacterStat stat, int amount)
{
	if (_statsMax.Contains(stat) == false)
	{
		LogStatError(stat);
		return;
	}

	_statsMax[stat] += amount;
	AdjustStatByValue(stat, amount);

	if (stat != ECharacterStat::HEALTH && stat != ECharacterStat::STAMINA && stat != ECharacterStat::MANA && stat != ECharacterStat::SPEED)
	{
		return;
	}

	ExecuteBindings(stat);
}

void UCharacterStatsComponent::SetStat(ECharacterStat stat, float amount)
{
	if (_stats.Contains(stat) == false)
	{
		LogStatError(stat);
		return;
	}

	_stats[stat] = amount;

	if (stat != ECharacterStat::HEALTH && stat != ECharacterStat::STAMINA && stat != ECharacterStat::MANA && stat != ECharacterStat::SPEED)
	{
		return;
	}

	ExecuteBindings(stat);
}

int UCharacterStatsComponent::GetStatAsValue(ECharacterStat stat) const
{
	if (_stats.Contains(stat) == false)
	{
		return 0;
	}

	return FMath::FloorToInt(_stats[stat]);
}

int UCharacterStatsComponent::GetStatAsPercentage(ECharacterStat stat) const
{
	if (_stats.Contains(stat) == false || _statsMax.Contains(stat) == false)
	{
		return 0;
	}

	return FMath::FloorToInt((_stats[stat] / _statsMax[stat]) * 100);
}

int UCharacterStatsComponent::GetStatBaseValue(ECharacterStat stat) const
{
	if (_statsBase.Contains(stat) == false)
	{
		return 0;
	}

	return _statsBase[stat];
}

int UCharacterStatsComponent::GetStatMaxValue(ECharacterStat stat) const
{
	if (_statsMax.Contains(stat) == false)
	{
		return 0;
	}

	return _statsMax[stat];
}

// Called every frame
void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_stats.Contains(ECharacterStat::STAMINA))
	{
		if (_staminaTimer > 0)
		{
			_staminaTimer -= DeltaTime;
		}
		else
		{
			_stats[ECharacterStat::STAMINA] = FMath::Clamp(_stats[ECharacterStat::STAMINA] += _staminaRegenPerTick * DeltaTime, 0, _statsMax[ECharacterStat::STAMINA]);
			ExecuteBindings(ECharacterStat::STAMINA);
		}
	}

	if (_stats.Contains(ECharacterStat::MANA))
	{
		if (_manaTimer > 0)
		{
			_manaTimer -= DeltaTime;
		}
		else
		{
			_stats[ECharacterStat::MANA] = FMath::Clamp(_stats[ECharacterStat::MANA] += _manaRegenPerTick * DeltaTime, 0, _statsMax[ECharacterStat::MANA]);
			ExecuteBindings(ECharacterStat::MANA);
		}
	}
}

// Called when the game starts
void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCharacterStatsComponent::ExecuteBindings(ECharacterStat stat)
{
	if (stat == ECharacterStat::HEALTH && OnHealthChanged.IsBound() == true)
	{
		OnHealthChanged.Execute(_stats[stat], _statsMax[stat]);
	}
	else if (stat == ECharacterStat::STAMINA && OnStaminaChanged.IsBound() == true)
	{
		OnStaminaChanged.Execute(_stats[stat], _statsMax[stat]);
	}
	else if (stat == ECharacterStat::MANA && OnManaChanged.IsBound() == true)
	{
		OnManaChanged.Execute(_stats[stat], _statsMax[stat]);
	}
	else if (stat == ECharacterStat::SPEED && OnSpeedChanged.IsBound() == true)
	{
		OnSpeedChanged.Execute(_stats[stat], 0.0f);
	}
}

void UCharacterStatsComponent::LogStatWarning(ECharacterStat stat)
{
	UE_LOG(LogTemp, Warning, TEXT("%s HAS NO BASE_%s"), *GetOwner()->GetName(), *UEnum::GetValueAsString(stat));
}

void UCharacterStatsComponent::LogStatError(ECharacterStat stat)
{
	UE_LOG(LogTemp, Error, TEXT("%s HAS NO %s STAT"), *GetOwner()->GetName(), *UEnum::GetValueAsString(stat));

}




