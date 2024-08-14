// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameLogic/Data/FoodDataAsset.h"
#include "IngredientDataAsset.generated.h"

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UIngredientDataAsset();

#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = IngredientData)
	void CreatePreparedIngredientDataAssets();

	virtual void UpdateFileName() override;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	TMap<EFoodPrepMethods, class UPreparedIngredientDataAsset*> PreparedIngredientDataAssets;

	
};
