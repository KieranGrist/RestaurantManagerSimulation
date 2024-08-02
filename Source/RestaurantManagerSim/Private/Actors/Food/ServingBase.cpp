// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food/ServingBase.h"

AServingBase::AServingBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Food, EFoodSubCategory::Serving);
}

// Called when the game starts or when spawned
void AServingBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AServingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
