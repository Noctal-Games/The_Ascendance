// Fill out your copyright notice in the Description page of Project Settings.

#include "HeldItem.h"
#include "TheAscendance/Characters/BaseCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHeldItem::AHeldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(m_MeshComponent, TEXT("HeldItem StaticMeshComponent failed to initialise"));
	m_MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	checkf(m_Collider, TEXT("HeldItem Collider failed to initialise"));
	m_Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_Collider->SetVisibility(false);
	m_Collider->SetHiddenInGame(true);
	m_Collider->SetupAttachment(m_MeshComponent);
}

void AHeldItem::Init(ABaseCharacter* owner)
{
	m_Owner = owner;
}

// Called when the game starts or when spawned
void AHeldItem::BeginPlay()
{
	Super::BeginPlay();
	
}
