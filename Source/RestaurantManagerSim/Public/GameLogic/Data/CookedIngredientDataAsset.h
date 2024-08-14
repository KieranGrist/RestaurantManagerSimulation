// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameLogic/Data/FoodDataAsset.h"
#include "CookedIngredientDataAsset.generated.h"

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UCookedIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UCookedIngredientDataAsset();

#if WITH_EDITOR
	virtual void UpdateFileName();
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	class UPreparedIngredientDataAsset* ParentPreparedIngredientDataAsset;

	// Seconds it takes to prepare this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	float CookTime = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	ECookingMethods  CookingMethod;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	float MiniumStorageTemperature = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	float MaxiumStorageTemperature = 10;

};
