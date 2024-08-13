// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Delivery/TruckBase.h"

ATruckBase::ATruckBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Delivery, EDeliverySubCategory::Truck);
}

void ATruckBase::BeginPlay()
{
	Super::BeginPlay();

}


void ATruckBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}