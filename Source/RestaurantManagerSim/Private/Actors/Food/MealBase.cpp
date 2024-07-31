// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food/MealBase.h"

AMealBase::AMealBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::WashingUp);
}

// Called when the game starts or when spawned
void AMealBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMealBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
