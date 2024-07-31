// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Architecture/WindowBase.h"

// Sets default values
AWindowBase::AWindowBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorCategory = FActorCategory(EMainCategory::Architecture, EArchitectureSubCategory::Window);
}

// Called when the game starts or when spawned
void AWindowBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWindowBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}