// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Data/GameDataAsset.h"
#include "PlayerDataAsset.generated.h"

// Game data class for managing player's money and other game-specific data
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UPlayerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPlayerDataAsset();

	void AddMoney(float InAddend);

	const float& GetCurrentMoney() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meal")
	TArray<FMeal> Meals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	FString CurrencySymbol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float PlayersMoney = 10000.0;
};

