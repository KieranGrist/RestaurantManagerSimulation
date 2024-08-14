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
		if (!current_pair.Value)
		{
			FString file_name = UFoodDataAsset::GetDisplayName(FActorCategory::EnumToString(current_pair.Key), DisplayName.ToString()).ToString();
			FString file_path = FString("/Game/Data/Food/PreparedIngredients");			
			UGameDataAsset* created_asset = CreateDataAsset(file_name, file_path, UPreparedIngredientDataAsset::StaticClass());
			current_pair.Value = Cast<UPreparedIngredientDataAsset>(created_asset);
		}
		current_pair.Value->PrepMethod = current_pair.Key;
		current_pair.Value->ParentIngredientDataAsset = this;
		current_pair.Value->UpdateFileName();
		current_pair.Value->CreateCookedIngredientDataAssets();
	}
}

void UIngredientDataAsset::UpdateFileName()
{
	Super::UpdateFileName();
}
