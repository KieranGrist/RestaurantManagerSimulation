// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Restaurant/FrontOfHouse/TrayBase.h"

// Sets default values
ATrayBase::ATrayBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrayBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATrayBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

