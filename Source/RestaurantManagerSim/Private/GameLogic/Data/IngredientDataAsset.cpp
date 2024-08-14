// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/IngredientDataAsset.h"
#include "GameLogic/Data/PreparedIngredientDataAsset.h"

UIngredientDataAsset::UIngredientDataAsset()
{

}

// Create prepared variants
void UIngredientDataAsset::CreatePreparedIngredientDataAssets()
{
	// Add new variants
	for (auto& current_pair : PreparedIngredientDataAssets)
	{
		if (current_pair.Value)
			continue;

		UGameDataAsset* created_asset = CreateDataAsset(FActorCategory::EnumToString(current_pair.Key) + " " + DisplayName.ToString(), FString("/Game/Data/Food/PreparedIngredients"), UPreparedIngredientDataAsset::StaticClass());
		current_pair.Value = Cast<UPreparedIngredientDataAsset>(created_asset);
	}
}

