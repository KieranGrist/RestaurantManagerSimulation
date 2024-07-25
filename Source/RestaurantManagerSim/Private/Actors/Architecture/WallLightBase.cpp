// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Architecture/WallLightBase.h"

// Sets default values
AWallLightBase::AWallLightBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Architecture, EArchitectureSubCategory::Light);
}

// Called when the game starts or when spawned
void AWallLightBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWallLightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}