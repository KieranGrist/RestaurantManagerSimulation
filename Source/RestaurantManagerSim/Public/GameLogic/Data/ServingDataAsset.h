// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Data/FoodDataAsset.h"
#include "ServingDataAsset.generated.h"

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UServingDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UServingDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ServingData)
	TSubclassOf<class AServingBase> ServingMethod;
};
