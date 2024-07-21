// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/CookingEquipment/MicrowaveBase.h"

// Sets default values
AMicrowaveBase::AMicrowaveBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMicrowaveBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMicrowaveBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

