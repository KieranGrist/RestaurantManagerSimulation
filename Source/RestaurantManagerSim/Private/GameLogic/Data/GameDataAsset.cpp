// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/GameDataAsset.h"
#include "EditorAssetLibrary.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "UObject/Package.h"
#include "Engine/World.h"
#include "Misc/PackageName.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "Actors/InteractableActorBase.h"

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

FEditorModeActorBase::FEditorModeActorBase(TSubclassOf<class AInteractableActorBase> InActorSpawnClass)
{
	ActorSpawnClass = InActorSpawnClass;
}

FEditorModeActors::FEditorModeActors()
{

}

UGameDataAsset::UGameDataAsset()
{
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

UGameDataAsset* UGameDataAsset::CreateDataAsset(const FString& InAssetName, const FString& InAssetPath, TSubclassOf<UGameDataAsset> InGameDataClass)
{
	// Get the Asset Tools module
	UE_LOG(LogTemp, Log, TEXT("Starting CreateDataAsset for %s in path %s"), *InAssetName, *InAssetPath);

	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsModule.Get();

	FString AssetNameSanitised = FormatDisplayNameToFileName(FName(InAssetName)).ToString();
	FString PackageName = InAssetPath + "/" + AssetNameSanitised;

	UE_LOG(LogTemp, Log, TEXT("Sanitized Asset Name: %s, Package Name: %s"), *AssetNameSanitised, *PackageName);

	// Create a new Data Asset package
	UPackage* Package = CreatePackage(*PackageName);
	if (!Package)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create package for %s"), *AssetNameSanitised);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Package created successfully for %s"), *AssetNameSanitised);
	}

	// Create the Data Asset
	UGameDataAsset* NewDataAsset = NewObject<UGameDataAsset>(Package, InGameDataClass, FName(*AssetNameSanitised), RF_Public | RF_Standalone);
	if (!NewDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create data asset %s"), *AssetNameSanitised);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Data Asset created successfully: %s"), *AssetNameSanitised);
	}

	// Mark the package as dirty so it gets saved
	Package->MarkPackageDirty();
	UE_LOG(LogTemp, Log, TEXT("Package marked dirty for %s"), *AssetNameSanitised);

	// Save the package using FSavePackageArgs
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	UE_LOG(LogTemp, Log, TEXT("Package file name: %s"), *PackageFileName);

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	SaveArgs.Error = GError;
	SaveArgs.bForceByteSwapping = false;
	SaveArgs.bWarnOfLongFilename = true;
	SaveArgs.bSlowTask = true;

	Package->FullyLoad();

	UE_LOG(LogTemp, Log, TEXT("Starting package save for %s"), *PackageFileName);
	FSavePackageResultStruct SaveResult = UPackage::Save(Package, NewDataAsset, *PackageFileName, SaveArgs);

	if (!SaveResult.IsSuccessful())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save package %s"), *PackageFileName);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Package saved successfully: %s"), *PackageFileName);
	}

	// Notify the editor about the new asset
	FAssetRegistryModule::AssetCreated(NewDataAsset);
	UE_LOG(LogTemp, Log, TEXT("Asset registered: %s"), *AssetNameSanitised);

	// Set additional properties if needed
	NewDataAsset->DisplayName = FName(InAssetName);
	NewDataAsset->UpdateFileName();
	UE_LOG(LogTemp, Log, TEXT("Asset properties updated: %s"), *AssetNameSanitised);

	return NewDataAsset;
}
