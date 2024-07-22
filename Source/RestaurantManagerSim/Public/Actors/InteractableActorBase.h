// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActorBase.generated.h"

enum class EMainCategory : uint8
{
	Architecture,
	Decoration,
	Delievery,
	Food,
	Kitchen,
	Restaurant
};

UENUM(BlueprintType)
enum class EArchitectureSubCategory : uint8
{
	None,
	Wall,
	Window,
	Light,
	Floor,
	Roof
};

UENUM(BlueprintType)
enum class EDecorationSubCategory : uint8
{
	None,
	Light,
	Plant,
	Rug,
};

UENUM(BlueprintType)
enum class EDeliverySubCategory : uint8
{
	None,
	Truck,
	Parcel,
	Crate,
};

UENUM(BlueprintType)
enum class EFoodSubCategory : uint8
{
	None,
	Ingredient,
	Meal,
	Trash
};

UENUM(BlueprintType)
enum class EKitchenSubCategory : uint8
{
	None,
	CookingEquipment,
	FoodPrep,
	Storage,
	WashingUp
};


UENUM(BlueprintType)
enum class ERestaurantSubCategory : uint8
{
	Stove UMETA(DisplayName = "Stove"),
	Oven UMETA(DisplayName = "Oven")
};

UCLASS()
class RESTAURANTMANAGERSIM_API  AInteractableActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActorBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//AGridSquare ParentSquare;

protected:
	float PurchaseCost;

	FName ActorName;


};
