// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food/IngredientBase.h"

AIngredientBase::AIngredientBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorData->ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::WashingUp);
}

// Called when the game starts or when spawned
void AIngredientBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIngredientBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
