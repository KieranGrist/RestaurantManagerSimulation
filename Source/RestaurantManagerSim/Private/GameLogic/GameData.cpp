// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/GameData.h"
#include "EditorAssetLibrary.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "UObject/Package.h"
#include "Engine/World.h"
#include "Misc/PackageName.h"
#include "AssetRegistry/AssetRegistryModule.h"

void UGameData::AddMoney(float InAddend)
{
	PlayersMoney += InAddend;
}

const float& UGameData::GetCurrentMoney() const
{
	return PlayersMoney;
}

const FString& FActorCategory::GetFullCategory() const
{
	return FullCategory;
}

const FString& FActorCategory::GetMainCategory() const
{
	return MainCategory;
}

const FString& FActorCategory::GetSubCategory() const
{
	return SubCategory;
}

void UGameDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    CreateFileName();
}

void UGameDataAsset::CreateFileName()
{
    FileName = FName("DA" + DisplayName.ToString().Replace(TEXT(" "), TEXT("")));
}

UPreparedIngredientDataAsset::UPreparedIngredientDataAsset()
{
    CookingMethods = 
    {
        {ECookingMethods::Fried, false},
        {ECookingMethods::Boiled, false},
        {ECookingMethods::Baked, false},
        {ECookingMethods::Grilled, false},
        {ECookingMethods::Raw, false},
        {ECookingMethods::Steamed, false},
        {ECookingMethods::Roasted, false},
        {ECookingMethods::Poached, false},
        {ECookingMethods::Sauteed, false},
        {ECookingMethods::Blanched, false}
    };
}

UIngredientDataAsset::UIngredientDataAsset()
{
    // Initialize IngredientPrepMethods with default values
        IngredientPrepMethods = 
        {
            {EFoodPrepMethods::Dicing, false},
            {EFoodPrepMethods::Slicing, false},
            {EFoodPrepMethods::Chopping, false},
            {EFoodPrepMethods::Grating, false},
            {EFoodPrepMethods::Peeling, false},
            {EFoodPrepMethods::Mincing, false},
            {EFoodPrepMethods::Blending, false},
            {EFoodPrepMethods::Mixing, false},
            {EFoodPrepMethods::Whisking, false},
            {EFoodPrepMethods::Marinating, false},
            {EFoodPrepMethods::Curing, false},
            {EFoodPrepMethods::Stuffing, false},
            {EFoodPrepMethods::Tenderizing, false},
            {EFoodPrepMethods::Shredding, false},
            {EFoodPrepMethods::Crushing, false},
            {EFoodPrepMethods::Juicing, false},
            {EFoodPrepMethods::Pureeing, false}
        };
    }

void UIngredientDataAsset::CreatePreparedVariants()
{
    // Remove obsolete variants
    TSet<EFoodPrepMethods> currentPrepMethods;
    for (const auto& ingredient_pair : IngredientPrepMethods)
    {
        if (ingredient_pair.Value)
        {
            currentPrepMethods.Add(ingredient_pair.Key);
        }
    }

    TArray<UPreparedIngredientDataAsset*> assetsToRemove;
    for (const auto& prepared_variant_pair : PreparedVariants)
    {
        if (!currentPrepMethods.Contains(prepared_variant_pair.Key))
        {
            assetsToRemove.Add(prepared_variant_pair.Value);
        }
    }

    for (UPreparedIngredientDataAsset* asset : assetsToRemove)
    {
        // Remove the asset from disk
        FString assetPath = FAssetRegistryModule::AssetNameToPath(asset->GetName());
        UEditorAssetLibrary (assetPath);
        PreparedVariants.Remove(asset->GetName());
    }

    // Add new variants
    for (const auto& ingredient_pair : IngredientPrepMethods)
    {
        if (!ingredient_pair.Value)
            continue;

        if (PreparedVariants.Contains(ingredient_pair.Key))
            continue;

        // Create a new prepared ingredient data asset
        UPreparedIngredientDataAsset* new_prepared_ingredient = NewObject<UPreparedIngredientDataAsset>(GetTransientPackage(), UPreparedIngredientDataAsset::StaticClass(), NAME_None, RF_Public | RF_Standalone);

        // Set the display name
        new_prepared_ingredient->DisplayName = FName(DisplayName.ToString() + " " + FActorCategory::EnumToString(ingredient_pair.Key));

        // Set the file name for the asset
        new_prepared_ingredient->CreateFileName();

        // Save the asset to the content browser
        FString asset_path = FString::Printf(TEXT("/Game/MyDataAssets/%s"), *new_prepared_ingredient->FileName.ToString());
        FAssetRegistryModule::AssetCreated(new_prepared_ingredient);
        UPackage::SavePackage(new_prepared_ingredient->GetOutermost(), new_prepared_ingredient, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *asset_path);

        // Add the new prepared ingredient to the array
        PreparedVariants.Add(ingredient_pair.Key, new_prepared_ingredient);
    }
}
