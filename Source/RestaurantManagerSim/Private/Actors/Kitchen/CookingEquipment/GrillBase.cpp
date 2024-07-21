// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Kitchen/CookingEquipment/GrillBase.h"

// Sets default values
AGrillBase::AGrillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrillBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

