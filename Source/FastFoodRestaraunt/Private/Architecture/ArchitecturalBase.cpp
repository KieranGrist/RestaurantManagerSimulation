// Fill out your copyright notice in the Description page of Project Settings.


#include "Architecture/BaseArchitecturalElement.h"

// Sets default values
ABaseArchitecturalElement::ABaseArchitecturalElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseArchitecturalElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseArchitecturalElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

