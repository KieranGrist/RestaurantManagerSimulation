// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Data/GameDataAsset.h"
#include "EditorModeDataAsset.generated.h"

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UEditorModeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UEditorModeDataAsset();

	UFUNCTION(CallInEditor, Category = EditorMode)
	void CreateEditorModeActorsMap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorMode)
	TArray<TSubclassOf<class AInteractableActorBase>> EditorModeBPActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorMode)
	TMap<FString, FEditorModeActors> EditorModeActorsMap;
};
