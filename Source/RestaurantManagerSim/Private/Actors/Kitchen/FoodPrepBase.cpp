// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/FoodPrepBase.h"

// Sets default values
AFoodPrepBase::AFoodPrepBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorData->ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::FoodPrep);
}

// Called when the game starts or when spawned
void AFoodPrepBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFoodPrepBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

