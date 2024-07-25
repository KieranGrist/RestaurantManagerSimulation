// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/CookingEquipment/CookingEquipmentBase.h"

// Sets default values
ACookingEquipmentBase::ACookingEquipmentBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::CookingEquipment);
}

// Called when the game starts or when spawned
void ACookingEquipmentBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACookingEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

