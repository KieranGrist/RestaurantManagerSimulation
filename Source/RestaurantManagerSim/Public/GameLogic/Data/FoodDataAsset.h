// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Data/GameDataAsset.h"
#include "FoodDataAsset.generated.h"

// Derived classes for specific data assets
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UFoodDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UFoodDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodData)
	FDateTime CreationTime = FDateTime::UtcNow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodData)
	float Quality;

};

