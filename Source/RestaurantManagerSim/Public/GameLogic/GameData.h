// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

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
		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		MainCategory = FActorCategory::EnumToString(InMainCategory);
		SubCategory = FActorCategory::EnumToString(InSubCategory);
		FullCategory = MainCategory + "::" + SubCategory;
	}

	template<typename EnumType>
	static FString EnumToString(EnumType InEnum)
	{
		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		UEnum* EnumPtr = StaticEnum<EnumType>();
		check(EnumPtr != nullptr);
		return EnumPtr->GetNameStringByValue((int64)InEnum);
	}

	// Convert string to enum
	template<typename EnumType>
	EnumType StringToEnum(FString InName)
	{
		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		UEnum* EnumPointer = StaticEnum<EnumType>();
		check(EnumPointer != nullptr);
		int64 EnumValue = EnumPointer->GetValueByName(FName(*InName));

		if (EnumValue == INDEX_NONE)
		{
			return EnumType(); // Default-constructed value (or handle the error appropriately)
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

	// Define a hash function for FActorCategory
	friend uint32 GetTypeHash(const FActorCategory& Category)
	{
		// Combine the hash values of the category fields
		return HashCombine(
			GetTypeHash(Category.FullCategory),
			HashCombine(
				GetTypeHash(Category.MainCategory),
				GetTypeHash(Category.SubCategory)
			)
		);
	}

	const FString& GetFullCategory() const;

	const FString& GetMainCategory() const;

	const FString& GetSubCategory() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString FullCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString MainCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString SubCategory;
};

USTRUCT(BlueprintType)
struct FSpawnableActors
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<class AInteractableActorBase>> MappedClasses;
};

// Data Asset classes for Food, Ingredient, and Meal data

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UGameDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UITexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActorCategory ActorCategory;
};

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
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Quality;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UArchitectureDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UDecorationDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:

};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UDeliveryDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UKitchenDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API URestaurantDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFoodPrepMethods, bool> IngredientPrepMethods;

	TArray<class UPreparedIngredientDataAsset>IngredientVariants;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UPreparedIngredientDataAsset : public UIngredientDataAsset
{
	GENERATED_BODY()

public:
	// No additional properties needed here, it inherits everything from UIngredientDataAsset
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
	float PlayersMoney = 10000.0f;
};
