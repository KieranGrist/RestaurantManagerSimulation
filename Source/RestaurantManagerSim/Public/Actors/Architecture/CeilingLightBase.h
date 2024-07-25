// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Architecture/ArchitecturalBase.h"
#include "CeilingLightBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API  ACeilingLightBase : public AArchitecturalBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACeilingLightBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
