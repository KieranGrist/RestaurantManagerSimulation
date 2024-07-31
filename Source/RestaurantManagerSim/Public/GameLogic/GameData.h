// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

// Main categories for actor classification
UENUM(BlueprintType)
enum class EMainCategory : uint8
{
	Error UMETA(DisplayName = "Error"),
	Architecture UMETA(DisplayName = "Architecture"),
	Decoration UMETA(DisplayName = "Decoration"),
	Delivery UMETA(DisplayName = "Delivery"),
	Food UMETA(DisplayName = "Food"),
	Kitchen UMETA(DisplayName = "Kitchen"),
	Restaurant UMETA(DisplayName = "Restaurant")
};

// Subcategories for Architecture
UENUM(BlueprintType)
enum class EArchitectureSubCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Door UMETA(DisplayName = "Door"),
	Floor UMETA(DisplayName = "Floor"),
	Light UMETA(DisplayName = "Light"),
	Roof UMETA(DisplayName = "Roof"),
	Wall UMETA(DisplayName = "Wall"),
	Window UMETA(DisplayName = "Window")
};

// Subcategories for Decoration
UENUM(BlueprintType)
enum class EDecorationSubCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Plant UMETA(DisplayName = "Plant"),
	Rug UMETA(DisplayName = "Rug")
};

// Subcategories for Delivery
UENUM(BlueprintType)
enum class EDeliverySubCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Crate UMETA(DisplayName = "Crate"),
	Parcel UMETA(DisplayName = "Parcel"),
	Truck UMETA(DisplayName = "Truck")
};

// Subcategories for Food
UENUM(BlueprintType)
enum class EFoodSubCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Ingredient UMETA(DisplayName = "Ingredient"),
	Meal UMETA(DisplayName = "Meal"),
	Serving UMETA(DisplayName = "Serving"),
	Waste UMETA(DisplayName = "Waste")
};

// Subcategories for Kitchen
UENUM(BlueprintType)
enum class EKitchenSubCategory : uint8
{
	None UMETA(DisplayName = "None"),
	CookingEquipment UMETA(DisplayName = "Cooking Equipment"),
	FoodPrep UMETA(DisplayName = "Food Prep"),
	Storage UMETA(DisplayName = "Storage"),
	WashingUp UMETA(DisplayName = "Washing Up")
};

// Subcategories for Restaurant
UENUM(BlueprintType)
enum class ERestaurantSubCategory : uint8
{
	None UMETA(DisplayName = "None"),
	FrontOfHouse UMETA(DisplayName = "Front of House"),
	Furniture UMETA(DisplayName = "Furniture")
};

// Food preparation methods
UENUM(BlueprintType)
enum class EFoodPrepMethods : uint8
{
	Fried UMETA(DisplayName = "Fried"),
	Boiled UMETA(DisplayName = "Boiled"),
	Baked UMETA(DisplayName = "Baked"),
	Grilled UMETA(DisplayName = "Grilled"),
	Raw UMETA(DisplayName = "Raw"),
	Steamed UMETA(DisplayName = "Steamed"),
	Roasted UMETA(DisplayName = "Roasted"),
	Poached UMETA(DisplayName = "Poached"),
	Sauteed UMETA(DisplayName = "Sauteed"),
	Blanch UMETA(DisplayName = "Blanch")
};

USTRUCT(BlueprintType)
struct FActorCategory
{
	GENERATED_BODY()

public:
	FActorCategory() {}

	template<typename EnumType>
	FActorCategory(EMainCategory InMainCategory, EnumType InSubCategory)
	{
		static_assert(TIsEnum<EnumType>::Value, "Only enum types are allowed");
		MainCategory = EnumToString(InMainCategory);
		SubCategory = EnumToString(InSubCategory);
		FullCategory = MainCategory + "::" + SubCategory;
	}

	// Returns the full category string
	const FString& GetFullCategory() const;

	// Returns the main category string
	const FString& GetMainCategory() const;

	// Returns the sub category string
	const FString& GetSubCategory() const;

	// Converts enum to string
	template<typename EnumType>
	static FString EnumToString(EnumType InEnum)
	{
		static_assert(TIsEnum<EnumType>::Value, "Only enum types are allowed");
		UEnum* EnumPtr = StaticEnum<EnumType>();
		check(EnumPtr != nullptr);
		return EnumPtr->GetNameStringByValue(static_cast<int64>(InEnum));
	}

	// Converts string to enum
	template<typename EnumType>
	static EnumType StringToEnum(const FString& InName)
	{
		static_assert(TIsEnum<EnumType>::Value, "Only enum types are allowed");
		UEnum* EnumPtr = StaticEnum<EnumType>();
		check(EnumPtr != nullptr);
		int64 EnumValue = EnumPtr->GetValueByName(FName(*InName));

		if (EnumValue == INDEX_NONE)
		{
			return EnumType(); // Default-constructed value
		}
		return static_cast<EnumType>(EnumValue);
	}

	bool operator==(const FActorCategory& Other) const
	{
		return FullCategory == Other.FullCategory &&
			MainCategory == Other.MainCategory &&
			SubCategory == Other.SubCategory;
	}

	bool operator!=(const FActorCategory& Other) const
	{
		return !(*this == Other);
	}

	// Hash function for FActorCategory
	friend uint32 GetTypeHash(const FActorCategory& Category)
	{
		return HashCombine(GetTypeHash(Category.FullCategory),
			HashCombine(GetTypeHash(Category.MainCategory),
				GetTypeHash(Category.SubCategory)));
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString FullCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString MainCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString SubCategory;
};

// Struct to manage actor base properties in editor mode
USTRUCT(BlueprintType)
struct FEditorModeActorBase
{
	GENERATED_BODY()

public:
	// The actual spawn class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AInteractableActorBase> ActorSpawnClass;

	// Instead of having 50 versions of wall blueprints, we use data assets which are less taxing 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UGameDataAsset*> GameDataArray;
};

// Struct to manage all editor mode actors
USTRUCT(BlueprintType)
struct FEditorModeActors
{
	GENERATED_BODY()

public:
	// Map of actor categories to their corresponding base properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FEditorModeActorBase> MappedClasses;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UGameDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	// Override PostEditChangeProperty
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void UpdateFileName();
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UITexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* MeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;
};

// Derived classes for specific data assets
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UFoodDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FoodName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime CreationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Quality;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UArchitectureDataAsset : public UGameDataAsset
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UDecorationDataAsset : public UGameDataAsset
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UDeliveryDataAsset : public UGameDataAsset
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UKitchenDataAsset : public UGameDataAsset
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API URestaurantDataAsset : public UGameDataAsset
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFoodPrepMethods, bool> IngredientPrepMethods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UPreparedIngredientDataAsset*> IngredientVariants;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UPreparedIngredientDataAsset : public UIngredientDataAsset
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UMealDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UIngredientDataAsset*> Ingredients;
};

// Game data class for managing player's money and other game-specific data
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UGameData : public UObject
{
	GENERATED_BODY()

public:
	void AddMoney(float InAddend);

	const float& GetCurrentMoney() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	FString CurrencySymbol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float PlayersMoney = 10000.0;

};