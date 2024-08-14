// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameLogic/Data/EditorModeDataAsset.h"
#include "GameLogic/Data/PlayerDataAsset.h"
#include "PlayerPawnBase.generated.h"

UCLASS()
class RESTAURANTMANAGERSIM_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorMode)
	UEditorModeDataAsset* EditorModeData;
	
	UPlayerDataAsset* PlayerDataAsset;
};
