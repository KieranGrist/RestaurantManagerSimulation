// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Kitchen/CookingEquipment/StoveBase.h"

// Sets default values
AStoveBase::AStoveBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStoveBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStoveBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

