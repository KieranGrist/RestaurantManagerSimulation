// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Data/FoodDataAsset.h"
#include "MealDataAsset.generated.h"

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UMealDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UMealDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MealData)
	TArray<FMealStage> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MealData)
	TArray<class UServingDataAsset*> ServingMethods;
};
