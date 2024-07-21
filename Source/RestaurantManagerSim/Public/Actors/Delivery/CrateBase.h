// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Delivery/DeliveryBase.h"
#include "CrateBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API ACrateBase : public ADeliveryBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACrateBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
