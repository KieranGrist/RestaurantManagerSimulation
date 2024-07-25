// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/KitchenEquipmentBase.h"

AKitchenEquipmentBase::AKitchenEquipmentBase()
{
	ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::None);
}

// Called when the game starts or when spawned
void AKitchenEquipmentBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AKitchenEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
