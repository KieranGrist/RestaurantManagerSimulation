// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Kitchen/CookingEquipment/CookingEquipmentBase.h"
#include "DeepFryerBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API  ADeepFryerBase : public ACookingEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeepFryerBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
