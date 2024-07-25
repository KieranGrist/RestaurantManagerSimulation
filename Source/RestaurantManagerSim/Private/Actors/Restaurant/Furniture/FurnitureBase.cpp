// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Restaurant/Furniture/FurnitureBase.h"

AFurnitureBase::AFurnitureBase()
{
	ActorCategory = FActorCategory(EMainCategory::Restaurant, ERestaurantSubCategory::Furniture);
}

// Called when the game starts or when spawned
void AFurnitureBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFurnitureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
