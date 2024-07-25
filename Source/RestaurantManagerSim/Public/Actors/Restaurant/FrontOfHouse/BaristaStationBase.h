// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Restaurant/FrontOfHouse/FrontOfHouseBase.h"
#include "BaristaStationBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API  ABaristaStationBase : public AFrontOfHouseBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaristaStationBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
