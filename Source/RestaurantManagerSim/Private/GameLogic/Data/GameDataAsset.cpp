// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/GameDataAsset.h"
#include "Actors/InteractableActorBase.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Editor.h"
#include "EditorAssetLibrary.h"
#include "Engine/World.h"
#include "FileHelpers.h"
#include "IAssetTools.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"

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

FEditorModeActorBase::FEditorModeActorBase()
{
}

FEditorModeActorBase::FEditorModeActorBase(TSubclassOf<class AInteractableActorBase> in_actor_spawn_class)
{
	ActorSpawnClass = in_actor_spawn_class;
}

FEditorModeActors::FEditorModeActors()
{

}

UGameDataAsset::UGameDataAsset()
{
}

void UGameDataAsset::PostEditChangeProperty(FPropertyChangedEvent& property_changed_event)
{
	UpdateFileName();
}

void UGameDataAsset::UpdateFileName()
{
	// Format DisplayName into a valid FileName
	FName old_file_name = FileName;
	FileName = FormatDisplayNameToFileName(DisplayName);

	if (old_file_name == FileName)
		return;

	// Get the current package path using the custom GetAssetFilePath() method
	FString package_path = FPackageName::GetLongPackagePath(GetAssetFilePath());
	FString new_asset_path = package_path + TEXT("/") + FileName.ToString();

	// Check if an asset with the new name already exists
	if (UEditorAssetLibrary::DoesAssetExist(new_asset_path))
	{
		UE_LOG(LogTemp, Error, TEXT("An asset with the name '%s' already exists at path: %s"), *FileName.ToString(), *new_asset_path);
		return;
	}

	// Ensure the new asset name is valid
	if (!FName::IsValidXName(FileName, INVALID_OBJECTNAME_CHARACTERS))
	{
		UE_LOG(LogTemp, Error, TEXT("The new asset name '%s' is invalid."), *FileName.ToString());
		return;
	}

	// Rename the asset
	FAssetToolsModule& asset_tools_module = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	TArray<FAssetRenameData> rename_data_array;
	rename_data_array.Emplace(this, package_path, FileName.ToString());

	asset_tools_module.Get().RenameAssets(rename_data_array);
	UE_LOG(LogTemp, Log, TEXT("Asset successfully renamed to: %s"), *FileName.ToString());

	// Get the package and save it to ensure the rename is persistent
	UPackage* outermost_package = GetOutermost();
	if (!outermost_package)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get the package for the asset."));
		return;
	}

	// Save the package
	FString package_file_name = FPackageName::LongPackageNameToFilename(outermost_package->GetName(), FPackageName::GetAssetPackageExtension());
	FSavePackageArgs save_package_args;
	FSavePackageResultStruct save_package_result = UPackage::Save(outermost_package, this, *package_file_name, save_package_args);

	if (!save_package_result.IsSuccessful())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save package %s"), *package_file_name);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Package saved successfully: %s"), *package_file_name);
	}

	// Fix redirectors in the folder to maintain references
	FixRedirectorsInFolder(package_path);
}


FName UGameDataAsset::FormatDisplayNameToFileName(FName in_display_name)
{
	return FName("DA" + in_display_name.ToString().Replace(TEXT(" "), TEXT("")));
}

UGameDataAsset* UGameDataAsset::CreateDataAsset(const FString& asset_name, const FString& asset_path, TSubclassOf<UGameDataAsset> game_data_class)
{
	// Get the Asset Tools module
	UE_LOG(LogTemp, Log, TEXT("Starting CreateDataAsset for %s in path %s"), *asset_name, *asset_path);

	FAssetToolsModule& asset_tools_module = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& asset_tools = asset_tools_module.Get();

	FString asset_name_sanitized = FormatDisplayNameToFileName(FName(asset_name)).ToString();
	FString package_name = asset_path + "/" + asset_name_sanitized;

	UE_LOG(LogTemp, Log, TEXT("Sanitized Asset Name: %s, Package Name: %s"), *asset_name_sanitized, *package_name);

	// Create a new Data Asset package
	UPackage* package = CreatePackage(*package_name);
	if (!package)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create package for %s"), *asset_name_sanitized);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Package created successfully for %s"), *asset_name_sanitized);
	}

	// Create the Data Asset
	UGameDataAsset* new_data_asset = NewObject<UGameDataAsset>(package, game_data_class, FName(*asset_name_sanitized), RF_Public | RF_Standalone);
	if (!new_data_asset)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create data asset %s"), *asset_name_sanitized);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Data Asset created successfully: %s"), *asset_name_sanitized);
	}

	// Mark the package as dirty so it gets saved
	package->MarkPackageDirty();
	UE_LOG(LogTemp, Log, TEXT("Package marked dirty for %s"), *asset_name_sanitized);

	// Save the package using FSavePackageArgs
	FString package_file_name = FPackageName::LongPackageNameToFilename(package_name, FPackageName::GetAssetPackageExtension());
	UE_LOG(LogTemp, Log, TEXT("Package file name: %s"), *package_file_name);

	FSavePackageArgs save_package_args;
	save_package_args.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	save_package_args.Error = GError;
	save_package_args.bForceByteSwapping = false;
	save_package_args.bWarnOfLongFilename = true;
	save_package_args.bSlowTask = true;

	package->FullyLoad();

	UE_LOG(LogTemp, Log, TEXT("Starting package save for %s"), *package_file_name);
	FSavePackageResultStruct save_package_result = UPackage::Save(package, new_data_asset, *package_file_name, save_package_args);

	if (!save_package_result.IsSuccessful())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save package %s"), *package_file_name);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Package saved successfully: %s"), *package_file_name);
	}

	// Notify the editor about the new asset
	FAssetRegistryModule::AssetCreated(new_data_asset);
	UE_LOG(LogTemp, Log, TEXT("Asset registered: %s"), *asset_name_sanitized);

	// Set additional properties if needed
	new_data_asset->DisplayName = FName(asset_name);
	new_data_asset->UpdateFileName();
	UE_LOG(LogTemp, Log, TEXT("Asset properties updated: %s"), *asset_name_sanitized);

	return new_data_asset;
}

void UGameDataAsset::FixRedirectorsInFolder(const FString& folder_path)
{
	TArray<UObjectRedirector*> redirector_array;

	// Get all asset paths in the folder
	TArray<FString> asset_paths = UEditorAssetLibrary::ListAssets(folder_path, /*bRecursive=*/ true, /*bIncludeFolder=*/ false);

	for (const FString& asset_path : asset_paths)
	{
		FAssetData asset_data = UEditorAssetLibrary::FindAssetData(asset_path);
		if (asset_data.IsRedirector())
		{
			UObjectRedirector* redirector = Cast<UObjectRedirector>(asset_data.GetAsset());
			if (redirector)
			{
				redirector_array.Add(redirector);
			}
		}
	}

	// Fix up redirectors if any are found
	if (redirector_array.Num() > 0)
	{
		FAssetToolsModule& asset_tools_module = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
		asset_tools_module.Get().FixupReferencers(redirector_array);
		UE_LOG(LogTemp, Log, TEXT("Fixed %d redirector(s) in folder: %s"), redirector_array.Num(), *folder_path);
	}
}

FString UGameDataAsset::GetAssetFilePath()
{
	// Get the outermost package of the asset
	UPackage* outermost_package = GetOutermost();

	// Get the package path
	FString package_path = FPackageName::LongPackageNameToFilename(outermost_package->GetName());

	return package_path;
}
