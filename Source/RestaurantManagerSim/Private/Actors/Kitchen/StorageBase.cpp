// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/StorageBase.h"


// Sets default values
AStorageBase::AStorageBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorData->ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::Storage);
}

// Called when the game starts or when spawned
void AStorageBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStorageBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

