// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/GameData.h"
#include "EditorAssetLibrary.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "UObject/Package.h"
#include "Engine/World.h"
#include "Misc/PackageName.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"


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

template<typename EnumType>
void UFoodDataAsset::CreateGameDataMaps(TMap<EnumType, bool>& EnumMap,TMap<EnumType, UGameDataAsset*>& CreatedDataMap, TSubclassOf<UGameDataAsset> GameDataClass, const FString& InPath)
{
    static_assert(TIsEnum<EnumType>::Value, "Only enum types are allowed");

    // Remove obsolete variants
    TSet<EnumType> current_prep_methods;
    for (const auto& enum_pair : EnumMap)
    {
        if (enum_pair.Value)
        {
            current_prep_methods.Add(enum_pair.Key);
        }
    }

    TArray<EnumType> assets_to_remove;
    for (const auto& prepared_variant_pair : CreatedDataMap)
    {
        if (!current_prep_methods.Contains(prepared_variant_pair.Key))
        {
            assets_to_remove.Add(prepared_variant_pair.Key);
        }
    }

    for (const auto& key : assets_to_remove)
    {
        UGameDataAsset* asset_to_remove = CreatedDataMap.FindRef(key);
        if (asset_to_remove)
        {
            // Remove the asset from disk
            FString asset_path = asset_to_remove->GetPathName();
            UEditorAssetLibrary::DeleteAsset(asset_path); // Correct method for deleting assets
            CreatedDataMap.Remove(key);
        }
    }

    // Add new variants
    for (const auto& enum_pair : EnumMap)
    {
        if (!enum_pair.Value)
            continue;

        if (CreatedDataMap.Contains(enum_pair.Key))
            continue;

        // Create a new prepared ingredient data asset
        UGameDataAsset* new_prepared_ingredient = NewObject<UGameDataAsset>(GetTransientPackage(), GameDataClass, NAME_None, RF_Public | RF_Standalone);

        // Set the display name
        new_prepared_ingredient->DisplayName = FName(DisplayName.ToString() + " " + FActorCategory::EnumToString(enum_pair.Key));

        // Set the file name for the asset
        new_prepared_ingredient->CreateFileName();

        // Save the asset to the content browser
        FString asset_path = FString::Printf(TEXT("%s%s"), *InPath, *new_prepared_ingredient->FileName.ToString());
        FAssetRegistryModule::AssetCreated(new_prepared_ingredient);

        // Save package
        FSavePackageArgs save_args;
        save_args.TopLevelFlags = RF_Public | RF_Standalone;
        UPackage::SavePackage(new_prepared_ingredient->GetOutermost(), new_prepared_ingredient, *asset_path, save_args);

        // Add the new prepared ingredient to the map
        CreatedDataMap.Add(enum_pair.Key, new_prepared_ingredient);
    }
}

// Create prepared variants
void UIngredientDataAsset::CreatePreparedIngredientDataAssets()
{
    CreateGameDataMaps(IngredientPrepMethods, PreparedIngredientDataAssets, UPreparedIngredientDataAsset::StaticClass(), TEXT("/Game/Content/Data/Food/Ingredient/PreparedIngredient/%s"));
}

void UPreparedIngredientDataAsset::CreateCookedIngredientDataAssets()
{
    CreateGameDataMaps<ECookingMethods>(CookingMethods, CookedIngredientDataAssets, UCookedIngredientDataAsset::StaticClass(), TEXT("/Game/Content/Data/Food/Ingredient/CookedIngredient/%s"));
}

