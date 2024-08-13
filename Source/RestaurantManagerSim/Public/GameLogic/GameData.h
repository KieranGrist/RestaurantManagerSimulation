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
	Error,
	Liquid,
	Gas,
	Solid,
	Rotten
};

// Food preparation methods
UENUM(BlueprintType)
enum class EFoodPrepMethods : uint8
{
	Whole UMETA(DisplayName = "Whole", ToolTip = "Using the whole ingredient"),
	Knife UMETA(DisplayName = "Knife", ToolTip = "Slicing, Cutting, Dicing, Chopping. Anything you could use a knife for"),
	Grate UMETA(DisplayName = "Grate", ToolTip = "Combines Grating and Shredding, Peeling"),
	Blender UMETA(DisplayName = "Blending", ToolTip = "Combines Blending, Mixing, Whisking, Pureeing"),
	Curer UMETA(DisplayName = "Curer", ToolTip = "Includes Marinating, Tenderizing, Aging, Smoking")
};

// Cooking methods
UENUM(BlueprintType)
enum class ECookingMethods : uint8
{
	Raw UMETA(DisplayName = "Raw", ToolTip = "Raw ingredient (does not need cooking, e.g., salad)"),
	Oven UMETA(DisplayName = "Oven", ToolTip = "Includes baking and roasting, for dry heat cooking methods"),
	Fryer UMETA(DisplayName = "Fryer", ToolTip = "For frying methods, including deep-frying, pan-frying"),
	Grill UMETA(DisplayName = "Grill", ToolTip = "For grilling, BBQ, and similar high-heat cooking methods"),
	Steamer UMETA(DisplayName = "Steamer", ToolTip = "Includes steaming, poaching, and any water-based cooking"),
	Pan UMETA(DisplayName = "Pan", ToolTip = "Includes boiling, blanching, sauteing, and similar stovetop methods")
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


	static FString GetMainCategory(const FString& InFullCategory)
	{
		FString Symbol = "::";
		int32 SymbolIndex = InFullCategory.Find(Symbol, ESearchCase::IgnoreCase, ESearchDir::FromStart);

		// Find the position of the symbol in the string
		if (SymbolIndex == INDEX_NONE)
			return FString();
		// Get the left part of the string before the symbol
		return InFullCategory.Left(SymbolIndex);
	}

	static FString GetSubCategory(const FString& InFullCategory)
	{
		FString Symbol = "::";
		int32 SymbolIndex = InFullCategory.Find(Symbol, ESearchCase::IgnoreCase, ESearchDir::FromStart);

		// Find the position of the symbol in the string
		if (SymbolIndex == INDEX_NONE)
			return FString();
		// Get the left part of the string before the symbol
		return InFullCategory.Right(SymbolIndex + 1);
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
	FEditorModeActorBase();
	FEditorModeActorBase(TSubclassOf<class AInteractableActorBase> InActorSpawnClass);

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
	UGameDataAsset();

#if WITH_EDITOR
	// Override PostEditChangeProperty
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void UpdateFileName();

	static FName FormatDisplayNameToFileName(FName InDisplayName);

	UGameDataAsset* CreateDataAsset(const FString& AssetName, const FString& AssetPath, TSubclassOf<UGameDataAsset> GameDataClass);
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
	float Cost = INDEX_NONE;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UArchitectureDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UArchitectureDataAsset();
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UDecorationDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UDecorationDataAsset();
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UDeliveryDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UDeliveryDataAsset();
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UKitchenDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UKitchenDataAsset();
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API URestaurantDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	URestaurantDataAsset();
};

// Derived classes for specific data assets
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UFoodDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UFoodDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodData)
	FDateTime CreationTime = FDateTime::UtcNow();

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
	TMap<EFoodPrepMethods, class UPreparedIngredientDataAsset*> PreparedIngredientDataAssets;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UPreparedIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UPreparedIngredientDataAsset();

#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = PreparedIngredientData)
	void CreateCookedIngredientDataAssets();
#endif

	// Float Represents cooking Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	TMap<ECookingMethods, class UCookedIngredientDataAsset*> CookedIngredientDataAssets;

	// Seconds it takes to prepare this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float PrepTime = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	EIngredientState IngredientState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float MiniumStorageTemperature = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PreparedIngredientData)
	float MaxiumStorageTemperature = 10;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UCookedIngredientDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UCookedIngredientDataAsset();

	// Seconds it takes to prepare this 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	float CookTime = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	EIngredientState IngredientState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	float MiniumStorageTemperature = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	float MaxiumStorageTemperature = 10;
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
	int32 StartingIngredientNeeded = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	UPreparedIngredientDataAsset* PreparedIngredient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	int32 PreparedIngredientNeeded = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	UCookedIngredientDataAsset* CookedIngredient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CookedIngredientData)
	int32 CookedIngredientNeeded = 1;
};

UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UServingDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UServingDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ServingData)
	TSubclassOf<class AServingBase> ServingMethod;
};


UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UMealDataAsset : public UFoodDataAsset
{
	GENERATED_BODY()

public:
	UMealDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MealData)
	TArray<FMealStage> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MealData)
	TArray<UServingDataAsset*> ServingMethods;
};

USTRUCT(BlueprintType)
struct FMeal
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meal)
	float MinPopularity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meal)
	float CurrentPopularity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meal)
	float MaxPopularity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meal)
	float RecipeCost = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meal)
	bool Unlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meal)
	UMealDataAsset* MealData;
};


UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UEditorModeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UEditorModeDataAsset();

	UFUNCTION(CallInEditor, Category = EditorMode)
	void CreateEditorModeActorsMap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorMode)
	TArray<TSubclassOf<class AInteractableActorBase>> EditorModeBPActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorMode)
	TMap<FString, FEditorModeActors> EditorModeActorsMap;
};

// Game data class for managing player's money and other game-specific data
UCLASS(BlueprintType)
class RESTAURANTMANAGERSIM_API UGameData : public UObject
{
	GENERATED_BODY()

public:
	UGameData();

	void AddMoney(float InAddend);

	const float& GetCurrentMoney() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	TArray<FMeal> Meals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	FString CurrencySymbol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float PlayersMoney = 10000.0;
};

