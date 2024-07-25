// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Restaurant/FrontOfHouse/FrontOfHouseBase.h"
#include "MenuBoardBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API  AMenuBoardBase : public AFrontOfHouseBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMenuBoardBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
