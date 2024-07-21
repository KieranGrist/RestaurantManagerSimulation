// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/FoodPrep/FoodProcessorBase.h"

// Sets default values
AFoodProcessorBase::AFoodProcessorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodProcessorBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFoodProcessorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

