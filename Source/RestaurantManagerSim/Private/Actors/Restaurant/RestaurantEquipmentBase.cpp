// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Restaurant/RestaurantEquipmentBase.h"

ARestaurantEquipmentBase::ARestaurantEquipmentBase()
{
	ActorCategory = FActorCategory(EMainCategory::Restaurant, ERestaurantSubCategory::None);
}

// Called when the game starts or when spawned
void ARestaurantEquipmentBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARestaurantEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
