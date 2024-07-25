// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActorBase.generated.h"

UENUM(BlueprintType)
enum class EMainCategory : uint8
{
	Error,
	Architecture,
	Decoration,
	Delivery,
	Food,
	Kitchen,
	Restaurant
};

UENUM(BlueprintType)
enum class EArchitectureSubCategory : uint8
{
	None,
	Door,
	Floor,
	Light,
	Roof,
	Wall,
	Window
};

UENUM(BlueprintType)
enum class EDecorationSubCategory : uint8
{
	None,
	Light,
	Plant,
	Rug
};

UENUM(BlueprintType)
enum class EDeliverySubCategory : uint8
{
	None,
	Crate,
	Parcel,
	Truck
};

UENUM(BlueprintType)
enum class EFoodSubCategory : uint8
{
	None,
	Ingredient,
	Meal,
	Serving,
	Waste
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
	None,
	FrontOfHouse,
	Furniture
};

USTRUCT(BlueprintType)
struct FActorCategory
{
	GENERATED_BODY()

public:
	FActorCategory();

	FActorCategory(EMainCategory InMainCategory, const FString& InSubCategory);
	FActorCategory(EMainCategory InMainCategory, EArchitectureSubCategory InSubCategory);
	FActorCategory(EMainCategory InMainCategory, EDecorationSubCategory InSubCategory);
	FActorCategory(EMainCategory InMainCategory, EDeliverySubCategory InSubCategory);
	FActorCategory(EMainCategory InMainCategory, EFoodSubCategory InSubCategory);
	FActorCategory(EMainCategory InMainCategory, EKitchenSubCategory InSubCategory);
	FActorCategory(EMainCategory InMainCategory, ERestaurantSubCategory InSubCategory);

	FString GetFullCategory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMainCategory MainCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SubCategory;
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
	void BuildActorCategory();

	const FActorCategory& GetActorCategory() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PurchaseCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActorCategory ActorCategory;
};
