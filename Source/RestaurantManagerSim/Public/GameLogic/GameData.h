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
enum class EIngredientState : uint8
{
	Liquid,
	Gas,
	Solid
};

// Food preparation methods
UENUM(BlueprintType)
enum class EFoodPrepMethods : uint8
{
	Dicing UMETA(DisplayName = "Dicing"),
	Slicing UMETA(DisplayName = "Slicing"),
	Chopping UMETA(DisplayName = "Chopping"),
	Grating UMETA(DisplayName = "Grating"),
	Peeling UMETA(DisplayName = "Peeling"),
	Mincing UMETA(DisplayName = "Mincing"),
	Blending UMETA(DisplayName = "Blending"),
	Mixing UMETA(DisplayName = "Mixing"),
	Whisking UMETA(DisplayName = "Whisking"),
	Marinating UMETA(DisplayName = "Marinating"),
	Curing UMETA(DisplayName = "Curing"),
	Stuffing UMETA(DisplayName = "Stuffing"),
	Tenderizing UMETA(DisplayName = "Tenderizing"),
	Shredding UMETA(DisplayName = "Shredding"),
	Crushing UMETA(DisplayName = "Crushing"),
	Juicing UMETA(DisplayName = "Juicing"),
	Pureeing UMETA(DisplayName = "Pureeing")
};

// Cooking methods
UENUM(BlueprintType)
enum class ECookingMethods : uint8
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
	Blanched UMETA(DisplayName = "Blanched")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ActorCategory)
	FString FullCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ActorCategory)
	FString MainCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ActorCategory)
	FString SubCategory;
};

// Struct to manage actor base properties in editor mode
USTRUCT(BlueprintType)
struct FEditorModeActorBase
{
	GENERATED_BODY()

public:
	// The actual spawn class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorModeActor)
	TSubclassOf<class AInteractableActorBase> ActorSpawnClass;

	// Instead of having 50 versions of wall blueprints, we use data assets which are less taxing 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorModeActor)
	TArray<UGameDataAsset*> GameDataArray;
};

// Struct to manage all editor mode actors
USTRUCT(BlueprintType)
struct FEditorModeActors
{
	GENERATED_BODY()

public:
	// Map of actor categories to their corresponding base properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorModeActors)
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
	static FName FormatDisplayNameToFileName(FName InDisplayName);
	UGameDataAsset* CreateDataAsset(FString AssetName, FString AssetPath, TSubclassOf<UGameDataAsset> GameDataClass);
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameData)
	FName DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameData)
	FName FileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameData)
	UTexture2D* UITexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameData)
	UMaterial* MeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameData)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameData)
	float Cost;
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

// Derived classes for specific data assets
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UFoodDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void CreateGameDataMaps(TMap<EnumType, bool>& EnumMap, TMap<EnumType, UGameDataAsset*>& CreatedDataMap, TSubclassOf<UGameDataAsset> GameDataClass, const FString& InPath);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodData)
	FDateTime CreationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodData)
	float Quality;

};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UIngredientDataAsset();

#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = IngredientData)
	void CreatePreparedIngredientDataAssets();
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	TMap<EFoodPrepMethods, bool> IngredientPrepMethods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	TMap <EFoodPrepMethods, UGameDataAsset*> PreparedIngredientDataAssets;
	
	// Seconds it takes to prepare this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	float PrepTime = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	EIngredientState IngredientState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	float MiniumStorageTemperature = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IngredientData)
	float MaxiumStorageTemperature = 10;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UPreparedIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	UPreparedIngredientDataAsset();

	UFUNCTION(CallInEditor, Category = IngredientData)
	void CreateCookedIngredientDataAssets();
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	TMap<ECookingMethods, bool> CookingMethods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	TMap<ECookingMethods, UGameDataAsset*> CookedIngredientDataAssets;

	// Seconds it takes to cook this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float CookingTime = 50;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UCookedIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

};

// Struct to manage a stage of making a meal e.g. Chicken and chips, would have Cooking Chicken, Cooking Chips
USTRUCT(BlueprintType)
struct FMealStage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	UIngredientDataAsset* StartingIngredient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	UPreparedIngredientDataAsset* PreparedIngredient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	UCookedIngredientDataAsset* CookedIngredient;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UServingDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ServingData)
	TSubclassOf<class AServingBase> ServingMethod;
};


UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UMealDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MealData)
	TArray<FMealStage> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MealData)
	TArray<UServingDataAsset*> ServingMethods;
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

