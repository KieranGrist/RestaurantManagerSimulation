// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Architecture/ArchitecturalBase.h"
#include "DoorBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIMULATION_API  ADoorBase : public AArchitecturalBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
