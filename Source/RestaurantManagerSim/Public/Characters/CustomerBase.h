// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "CustomerBase.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTMANAGERSIM_API ACustomerBase : public ACharacterBase
{
	GENERATED_BODY()
public:

	// Sets default values for this character's properties
	ACustomerBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
