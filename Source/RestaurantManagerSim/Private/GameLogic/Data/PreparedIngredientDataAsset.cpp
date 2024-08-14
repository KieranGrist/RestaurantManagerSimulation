// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/PreparedIngredientDataAsset.h"
#include "GameLogic/Data/CookedIngredientDataAsset.h"

UPreparedIngredientDataAsset::UPreparedIngredientDataAsset()
{

}

void UPreparedIngredientDataAsset::CreateCookedIngredientDataAssets()
{
	// Add new variants
	for (auto& current_pair : CookedIngredientDataAssets)
	{
		if (current_pair.Value)
			continue;
		UGameDataAsset* created_asset = CreateDataAsset(FActorCategory::EnumToString(current_pair.Key) + " " + DisplayName.ToString(), FString("/Game/Data/Food/CookedIngredients"), UCookedIngredientDataAsset::StaticClass());
		current_pair.Value = Cast< UCookedIngredientDataAsset>(created_asset);
	}
}
