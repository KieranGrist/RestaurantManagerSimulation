// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StaffBase.h"

// Sets default values
AStaffBase::AStaffBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStaffBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStaffBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStaffBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

