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

}

UPreparedIngredientDataAsset::UPreparedIngredientDataAsset()
{

}

template<typename EnumType>
void UFoodDataAsset::CreateGameDataMaps(const TArray<EnumType>& InEnums, TMap<EnumType, UGameDataAsset*>& CreatedDataMap, TSubclassOf<UGameDataAsset> InGameDataClass, const FString& InPath)
{
	static_assert(TIsEnum<EnumType>::Value, "Only enum types are allowed");

	TArray<EnumType> assets_to_remove;
	for (const auto& prepared_variant_pair : CreatedDataMap)
	{
		if (!InEnums.Contains(prepared_variant_pair.Key))
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
		}			
		CreatedDataMap.Remove(key);
	}

	// Add new variants
	for (const auto& current_enum : InEnums)
	{
		if (CreatedDataMap.Contains(current_enum))
			continue;		

		CreatedDataMap.Add(current_enum, CreateDataAsset(DisplayName.ToString() + " " + FActorCategory::EnumToString(current_enum), InPath, InGameDataClass));
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

