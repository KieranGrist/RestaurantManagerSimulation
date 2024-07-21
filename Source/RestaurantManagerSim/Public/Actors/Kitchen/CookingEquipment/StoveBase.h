// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Kitchen/KitchenEquipmentBase.h"
#include "StoveBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API  AStoveBase : public AKitchenEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStoveBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
