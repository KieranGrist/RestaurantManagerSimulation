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
#include "Actors/InteractableActorBase.h"

UPlayerData::UPlayerData()
{
}

void UPlayerData::AddMoney(float InAddend)
{
	PlayersMoney += InAddend;
}

const float& UPlayerData::GetCurrentMoney() const
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

UIngredientDataAsset::UIngredientDataAsset()
{

}

UPreparedIngredientDataAsset::UPreparedIngredientDataAsset()
{

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

// Create prepared variants
void UIngredientDataAsset::CreatePreparedIngredientDataAssets()
{
	// Add new variants
	for (auto& current_pair : PreparedIngredientDataAssets)
	{
		if (current_pair.Value)
			continue;

		UGameDataAsset* created_asset = CreateDataAsset(DisplayName.ToString() + " " + FActorCategory::EnumToString(current_pair.Key), FString("/Game/Data/Food/PreparedIngredients"), UPreparedIngredientDataAsset::StaticClass());
		current_pair.Value = Cast<UPreparedIngredientDataAsset>(created_asset);
	}
}

void UPreparedIngredientDataAsset::CreateCookedIngredientDataAssets()
{
	// Add new variants
	for (auto& current_pair : CookedIngredientDataAssets)
	{
		if (current_pair.Value)
			continue;
		UGameDataAsset* created_asset = CreateDataAsset(DisplayName.ToString() + " " + FActorCategory::EnumToString(current_pair.Key), FString("/Game/Data/Food/CookedIngredients"), UCookedIngredientDataAsset::StaticClass());
		current_pair.Value = Cast< UCookedIngredientDataAsset>(created_asset);
	}
}


UMealDataAsset::UMealDataAsset()
{

}

UServingDataAsset::UServingDataAsset()
{

}

UCookedIngredientDataAsset::UCookedIngredientDataAsset()
{

}

UFoodDataAsset::UFoodDataAsset()
{

}

URestaurantDataAsset::URestaurantDataAsset()
{

}

UKitchenDataAsset::UKitchenDataAsset()
{

}

UDeliveryDataAsset::UDeliveryDataAsset()
{

}

UDecorationDataAsset::UDecorationDataAsset()
{

}

UArchitectureDataAsset::UArchitectureDataAsset()
{

}

UEditorModeDataAsset::UEditorModeDataAsset()
{
}

void UEditorModeDataAsset::CreateEditorModeActorsMap()
{
	for (TSubclassOf<AInteractableActorBase> actor_class : EditorModeBPActors)
	{
		if (!actor_class)
		{
			continue;
		}

		// Access the class default object (CDO)
		AInteractableActorBase* default_actor = actor_class->GetDefaultObject<AInteractableActorBase>();

		if (!default_actor)
			continue;

		const FString& actor_category = default_actor->GetActorCategory().GetFullCategory();
		
		// Add the actor class to the map under its category
		FEditorModeActors& spawnable_actors = EditorModeActorsMap.FindOrAdd(actor_category);
		if(spawnable_actors.MappedClasses.Find(actor_class->GetName()))
			continue;

		spawnable_actors.MappedClasses.Add(actor_class->GetName(), FEditorModeActorBase(actor_class));
	}

	EditorModeActorsMap.KeySort([](const FString& A, const FString& B)
		{
			FString main_category_a = FActorCategory::GetMainCategory(A);
			FString main_category_b = FActorCategory::GetMainCategory(B);
			FString sub_category_a = FActorCategory::GetSubCategory(A);
			FString sub_category_b = FActorCategory::GetSubCategory(B);

			if (main_category_a < main_category_b)
				return true;

			if (main_category_a > main_category_b)
				return false;

			if (sub_category_a < sub_category_b)
				return true;

			if (sub_category_a > sub_category_b)
				return false;
			return false;
		});
}

FEditorModeActorBase::FEditorModeActorBase()
{
}

FEditorModeActorBase::FEditorModeActorBase(TSubclassOf<class AInteractableActorBase> InActorSpawnClass)
{
	ActorSpawnClass = InActorSpawnClass;
}
