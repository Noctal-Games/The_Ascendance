// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THEASCENDANCE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseHealth;
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseStamina;
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseMana;
	UPROPERTY(EditDefaultsOnly, Category = "STATS")
	float _baseSpeed;
};
