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
	UpdateFileName();
}

void UGameDataAsset::UpdateFileName()
{
	FileName = FormatDisplayNameToFileName(DisplayName);
}

FName UGameDataAsset::FormatDisplayNameToFileName(FName InDisplayName)
{
	return FName("DA" + InDisplayName.ToString().Replace(TEXT(" "), TEXT("")));
}

UIngredientDataAsset::UIngredientDataAsset()
{
	// Initialize IngredientPrepMethods with default values
	IngredientPrepMethods =
	{
		{EFoodPrepMethods::Cutting, false},
		{EFoodPrepMethods::Slicing, false},
		{EFoodPrepMethods::Grating, false},
		{EFoodPrepMethods::Blending, false},
		{EFoodPrepMethods::Marinating, false}
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
		{ECookingMethods::Steamed, false}
	};
}

template<typename EnumType>
void UFoodDataAsset::CreateGameDataMaps(TMap<EnumType, bool>& EnumMap, TMap<EnumType, UGameDataAsset*>& CreatedDataMap, TSubclassOf<UGameDataAsset> InGameDataClass, const FString& InPath)
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

		CreatedDataMap.Add(enum_pair.Key, CreateDataAsset(DisplayName.ToString() + " " + FActorCategory::EnumToString(enum_pair.Key), InPath, InGameDataClass));
	}
}

// Define the factory function
UGameDataAsset* UGameDataAsset::CreateDataAsset(const FString& InAssetName, const FString& InAssetPath, TSubclassOf<UGameDataAsset> InGameDataClass)
{
	// Get the Asset Tools module
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsModule.Get();

	FString AssetNameSanitised = FormatDisplayNameToFileName(FName(InAssetName)).ToString();
	FString PackageName = InAssetPath + "/" + AssetNameSanitised;

	// Create a new Data Asset package
	UPackage* Package = CreatePackage(*PackageName);
	if (!Package)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create package for %s"), *AssetNameSanitised);
		return nullptr;
	}

	// Create the Data Asset
	UGameDataAsset* NewDataAsset = NewObject<UGameDataAsset>(Package, InGameDataClass, FName(*AssetNameSanitised), RF_Public | RF_Standalone);
	if (!NewDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create data asset %s"), *AssetNameSanitised);
		return nullptr;
	}

	// Mark the package as dirty so it gets saved
	Package->MarkPackageDirty();

	// Save the package using FSavePackageArgs
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	SaveArgs.Error = GError;
	SaveArgs.bForceByteSwapping = false;
	SaveArgs.bWarnOfLongFilename = true;
	SaveArgs.bSlowTask = true;
	//SaveArgs.bConcurrentSave = true;

	if (!UPackage::Save(Package, NewDataAsset, *PackageFileName, SaveArgs).IsSuccessful())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save package %s"), *PackageFileName);
		return nullptr;
	}

	// Notify the editor about the new asset
	FAssetRegistryModule::AssetCreated(NewDataAsset);

	// Set additional properties if needed
	NewDataAsset->DisplayName = FName(InAssetName);
	NewDataAsset->UpdateFileName();

	return NewDataAsset;
}

// Create prepared variants
void UIngredientDataAsset::CreatePreparedIngredientDataAssets()
{
	CreateGameDataMaps(IngredientPrepMethods, PreparedIngredientDataAssets, UPreparedIngredientDataAsset::StaticClass(), FString("/Game/Data/Food/PreparedIngredients"));
}

void UPreparedIngredientDataAsset::CreateCookedIngredientDataAssets()
{
	CreateGameDataMaps(CookingMethods, CookedIngredientDataAssets, UCookedIngredientDataAsset::StaticClass(), FString("/Game/Data/Food/CookedIngredients"));
}

