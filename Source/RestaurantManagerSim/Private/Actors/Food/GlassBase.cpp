// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food/GlassBase.h"

AGlassBase::AGlassBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Kitchen, EKitchenSubCategory::WashingUp);
}

// Called when the game starts or when spawned
void AGlassBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGlassBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
