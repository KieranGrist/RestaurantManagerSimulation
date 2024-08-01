// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food/PlateBase.h"

APlateBase::APlateBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Food, EFoodSubCategory::Plate);
}

// Called when the game starts or when spawned
void APlateBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
