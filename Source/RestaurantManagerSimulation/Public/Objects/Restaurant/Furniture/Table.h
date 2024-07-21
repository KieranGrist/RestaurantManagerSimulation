// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Furniture/FurnitureBase.h"
#include "Table.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIMULATION_API  ATable : public AFurnitureBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
