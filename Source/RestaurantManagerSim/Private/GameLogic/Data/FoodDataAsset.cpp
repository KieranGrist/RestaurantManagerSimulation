// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/FoodDataAsset.h"

UFoodDataAsset::UFoodDataAsset()
{

}

FName UFoodDataAsset::GetDisplayName(const FString& InEnumString, const FString& InDisplayName)
{
	FString new_file_name;
	new_file_name += InEnumString;
	new_file_name += " ";
	new_file_name += InDisplayName;
	return FName(new_file_name);
}
