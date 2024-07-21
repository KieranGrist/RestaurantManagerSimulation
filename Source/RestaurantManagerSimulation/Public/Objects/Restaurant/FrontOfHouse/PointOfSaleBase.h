// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Restaurant/RestaurantEquipmentBase.h"
#include "PointOfSaleBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIMULATION_API  APointOfSaleBase : public ARestaurantEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APointOfSaleBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
