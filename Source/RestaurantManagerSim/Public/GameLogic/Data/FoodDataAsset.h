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

#if WITH_EDITOR
	static FName GetDisplayName(const FString& InEnumString, const FString& InDisplayName);
#endif
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodDataAsset)
	EIngredientState IngredientState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodDataAsset)
	EFoodPrepMethods FoodPrep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodDataAsset)
	FDateTime CreationTime = FDateTime::UtcNow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodDataAsset)
	float Quality;

};

