// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/CookedIngredientDataAsset.h"
#include "GameLogic/Data/PreparedIngredientDataAsset.h"

UCookedIngredientDataAsset::UCookedIngredientDataAsset()
{

}

void UCookedIngredientDataAsset::UpdateFileName()
{
	DisplayName =  UFoodDataAsset::GetDisplayName(FActorCategory::EnumToString(CookingMethod), ParentPreparedIngredientDataAsset->DisplayName.ToString());
	
	Super::UpdateFileName();
}

