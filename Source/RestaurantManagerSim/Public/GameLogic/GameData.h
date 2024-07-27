// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

USTRUCT(BlueprintType)
struct FActorCategory
{
	GENERATED_BODY()

public:
	FActorCategory();

	template<typename EnumType>
	FActorCategory(EMainCategory InMainCategory, EnumType InSubCategory)
	{
		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		MainCategory = FActorCategory::GetEnumNameString(InMainCategory);
		SubCategory = FActorCategory::GetEnumNameString(InSubCategory);
		FullCategory = MainCategory + "::" + SubCategory;
	}
	const FString& GetFullCategory() const;

	const FString& GetMainCategory() const;

	const FString& GetSubCategory() const;

	template<typename EnumType>
	static FString GetEnumNameString(EnumType InEnum)
	{
		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		UEnum* enum_ptr = StaticEnum<EnumType>();
		check(enum_ptr != nullptr);
		// Get the string representation of the enum value
		return enum_ptr->GetNameStringByValue((int64)InEnum);
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString FullCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString MainCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString SubCategory;
};

USTRUCT(BlueprintType)
struct FMoney
{
    GENERATED_BODY()

public:
     // Default constructor
    FMoney()
        : Amount(0.0f) {}

    // Parameterized constructor
    FMoney(float InAmount)
        : Amount(FMath::Max(0.0f, InAmount)) {}

    // Overload addition operator
    FMoney operator+(const FMoney& Other) const
    {
        return FMoney(Amount + Other.Amount);
    }

    // Overload subtraction operator
    FMoney operator-(const FMoney& Other) const
    {
        return FMoney(FMath::Max(0.0f, Amount - Other.Amount));
    }

    // Overload assignment operator for addition
    FMoney& operator+=(const FMoney& Other)
    {
        Amount += Other.Amount;
        return *this;
    }

    // Overload assignment operator for subtraction
    FMoney& operator-=(const FMoney& Other)
    {
        Amount = FMath::Max(0.0f, Amount - Other.Amount);
        return *this;
    }

    // Overload equality operator
    bool operator==(const FMoney& Other) const
    {
        return Amount == Other.Amount;
    }

    // Overload inequality operator
    bool operator!=(const FMoney& Other) const
    {
        return !(*this == Other);
    }

    // Utility function to check if the amount is valid
    bool IsValid() const
    {
        return Amount >= 0.0f;
    }

    float GetAmount()
protected:
    // Amount of money
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
    float Amount;
};

struct FIngredientData : public FTableRowBase
{
    GENERATED_BODY()

public:
};

UCLASS()
class RESTAURANTMANAGERSIM_API UGameData : public UObject
{
	GENERATED_BODY()
	
public:
    // Currency symbol, e.g., "$", "€"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
    FString CurrencySymbol;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
    FMoney PlayersMoney = FMoney(10000);
};



