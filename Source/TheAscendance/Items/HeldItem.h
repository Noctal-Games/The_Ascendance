// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "TheAscendance/Items/Enums/WeaponType.h"
#include "HeldItem.generated.h"

class ABaseCharacter;
class UBoxComponent;
struct FItemData;
struct FWeaponData;
struct FWeaponTypeData;

UCLASS()
class THEASCENDANCE_API AHeldItem : public AItem
{
	GENERATED_BODY()
	
public:	
	AHeldItem();

	void SetItemOwner(ABaseCharacter* owner);

	virtual void Init(FItemData* itemData) override;
	virtual void SetStaticMesh() override;
	void UnEquip();

	bool StartPrimaryAttack();
	bool StartSecondaryAttack();

	void EndAttack();

	EWeaponType GetWeaponType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void EndPrimaryAttack();
	void EndSecondaryAttack();

private:
	TWeakObjectPtr<ABaseCharacter> m_Owner = nullptr;

	UPROPERTY()
	TObjectPtr<UBoxComponent> m_Collider = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<ABaseCharacter>> m_HitCharacters;

	TSharedPtr<FWeaponData> m_WeaponData = nullptr;
	TSharedPtr<FWeaponTypeData> m_WeaponTypeData = nullptr;

	bool m_IsPrimaryAttacking = false;
};
