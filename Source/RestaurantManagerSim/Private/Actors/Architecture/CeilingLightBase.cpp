// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Architecture/CeilingLightBase.h"

// Sets default values
ACeilingLightBase::ACeilingLightBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Architecture, EArchitectureSubCategory::Light);
}

// Called when the game starts or when spawned
void ACeilingLightBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACeilingLightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}