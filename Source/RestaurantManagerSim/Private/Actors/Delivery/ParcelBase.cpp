// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Delivery/ParcelBase.h"

// Sets default values
AParcelBase::AParcelBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Delivery, EDeliverySubCategory::Parcel);
}

// Called when the game starts or when spawned
void AParcelBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AParcelBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}