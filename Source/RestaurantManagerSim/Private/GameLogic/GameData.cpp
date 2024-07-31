// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/GameData.h"

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
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UGameDataAsset, Name))
	{
		UpdateFileName();
	}
}

void UGameDataAsset::UpdateFileName()
{
	// Convert name to string and remove spaces
	FString new_name = Name.ToString().Replace(TEXT(" "), TEXT(""));

	// Update the asset's file name
	if (new_name.IsEmpty())
		return;

	// Get the package for the asset
	UPackage* package = GetPackage();

	if (!package)
		return;
	// Construct the new package path
	FString package_path = package->GetName();
	FString new_package_path = FPaths::Combine(FPaths::GetPath(package_path), new_name);

	if (package->Rename(*new_package_path))
		// Save the package if the rename was successful
		UPackage::SavePackage(package, nullptr, EObjectFlags::RF_Standalone, *new_package_path);

	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to rename package to: %s"), *new_package_path);

}