// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Kitchen/CookingEquipment/CookingEquipmentBase.h"
#include "ToasterBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API  AToasterBase : public ACookingEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToasterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
