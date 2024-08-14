// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/PlayerDataAsset.h"

UPlayerDataAsset::UPlayerDataAsset()
{
}

void UPlayerDataAsset::AddMoney(float InAddend)
{
	PlayersMoney += InAddend;
}

const float& UPlayerDataAsset::GetCurrentMoney() const
{
	return PlayersMoney;
}
