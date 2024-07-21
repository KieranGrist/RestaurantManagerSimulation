// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObjectBase.h"
#include "FurnitureBase.generated.h"

/**
 * 
 */
UCLASS()
class FASTFOODRESTARAUNT_API AFurnitureBase : public AInteractableObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFurnitureBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
