// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Kitchen/CookingEquipment/ToasterBase.h"

// Sets default values
AToasterBase::AToasterBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AToasterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AToasterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

