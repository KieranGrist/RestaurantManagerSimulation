// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Data/FoodDataAsset.h"
#include "PreparedIngredientDataAsset.generated.h"

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UPreparedIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPreparedIngredientDataAsset();

#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = PreparedIngredientData)
	void CreateCookedIngredientDataAssets();
#endif

	// Float Represents cooking Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	TMap<ECookingMethods, class UCookedIngredientDataAsset*> CookedIngredientDataAssets;

	// Seconds it takes to prepare this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float PrepTime = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	EIngredientState IngredientState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float MiniumStorageTemperature = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float MaxiumStorageTemperature = 10;
};
