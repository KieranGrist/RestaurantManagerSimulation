// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Restaurant/FrontOfHouse/TillBase.h"

// Sets default values
ATillBase::ATillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATillBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

