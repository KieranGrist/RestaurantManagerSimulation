// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FastFoodRestarauntGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FASTFOODRESTARAUNT_API AFastFoodRestarauntGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFastFoodRestarauntGameModeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
