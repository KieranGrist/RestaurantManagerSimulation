// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Delivery/CrateBase.h"

// Sets default values
ACrateBase::ACrateBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Delivery, EDeliverySubCategory::Crate);
}

// Called when the game starts or when spawned
void ACrateBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACrateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}