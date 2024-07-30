// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Delivery/DeliveryBase.h"

// Sets default values
ADeliveryBase::ADeliveryBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorData->ActorCategory = FActorCategory(EMainCategory::Delivery, EDeliverySubCategory::None);
}

// Called when the game starts or when spawned
void ADeliveryBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADeliveryBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}