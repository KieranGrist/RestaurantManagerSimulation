// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Restaurant/FrontOfHouse/FrontOfHouseBase.h"

// Sets default values
AFrontOfHouseBase::AFrontOfHouseBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorData->ActorCategory = FActorCategory(EMainCategory::Restaurant, ERestaurantSubCategory::FrontOfHouse);
}

// Called when the game starts or when spawned
void AFrontOfHouseBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFrontOfHouseBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

