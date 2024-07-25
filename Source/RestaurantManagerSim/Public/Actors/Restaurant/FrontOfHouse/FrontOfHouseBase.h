// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Restaurant/RestaurantEquipmentBase.h"
#include "FrontOfHouseBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API AFrontOfHouseBase : public ARestaurantEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFrontOfHouseBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
