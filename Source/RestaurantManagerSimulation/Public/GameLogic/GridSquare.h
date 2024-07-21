// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSquare.generated.h"

UCLASS()
class RESTAURANTMANAGERSIMULATION_API  AGridSquare : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridSquare();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
