// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeldItem.generated.h"

class ABaseCharacter;
class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class THEASCENDANCE_API AHeldItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeldItem();
	
	void Init(ABaseCharacter* owner);
	//void UpdateItem();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<ABaseCharacter> m_Owner = nullptr;

	UPROPERTY()
	TObjectPtr<UBoxComponent> m_Collider = nullptr;
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> m_MeshComponent = nullptr;
	UPROPERTY()
	TSoftObjectPtr<UStaticMesh> m_Mesh = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<ABaseCharacter>> m_HitCharacters;
};
