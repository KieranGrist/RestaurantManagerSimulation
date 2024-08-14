// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/PreparedIngredientDataAsset.h"
#include "GameLogic/Data/CookedIngredientDataAsset.h"
#include "GameLogic/Data/IngredientDataAsset.h"

UPreparedIngredientDataAsset::UPreparedIngredientDataAsset()
{

}

void UPreparedIngredientDataAsset::CreateCookedIngredientDataAssets()
{
	// Add new variants
	for (auto& current_pair : CookedIngredientDataAssets)
	{
		if (!current_pair.Value)
		{
			FString file_name = UFoodDataAsset::GetDisplayName(FActorCategory::EnumToString(current_pair.Key), DisplayName.ToString()).ToString();
			FString file_path = FString("/Game/Data/Food/CookedIngredients");
			UGameDataAsset* created_asset = CreateDataAsset(file_name, file_path, UCookedIngredientDataAsset::StaticClass());
			current_pair.Value = Cast<UCookedIngredientDataAsset>(created_asset);
		}
		current_pair.Value->CookingMethod = current_pair.Key;
		current_pair.Value->ParentPreparedIngredientDataAsset = this; 
		current_pair.Value->UpdateFileName();
	}
}

void UPreparedIngredientDataAsset::UpdateFileName()
{
	DisplayName = UFoodDataAsset::GetDisplayName(FActorCategory::EnumToString(PrepMethod), ParentIngredientDataAsset->DisplayName.ToString());

	Super::UpdateFileName();
}


