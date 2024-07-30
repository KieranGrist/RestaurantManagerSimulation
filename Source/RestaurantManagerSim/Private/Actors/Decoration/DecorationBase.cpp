// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Decoration/DecorationBase.h"

ADecorationBase::ADecorationBase()
{
	ActorData->ActorCategory = FActorCategory(EMainCategory::Decoration, EDecorationSubCategory::None);
}

// Called when the game starts or when spawned
void ADecorationBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADecorationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
