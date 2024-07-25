// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"


// Sets default values
AInteractableActorBase::AInteractableActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BuildActorCategory();
}

// Called when the game starts or when spawned
void AInteractableActorBase::BeginPlay()
{
	Super::BeginPlay();
	BuildActorCategory();
}

// Called every frame
void AInteractableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableActorBase::BuildActorCategory()
{

}

const FActorCategory& AInteractableActorBase::GetActorCategory() const
{
	return ActorCategory;
}

FActorCategory::FActorCategory()
{
	MainCategory = EMainCategory::Error;

	SubCategory = "";
};

FActorCategory::FActorCategory(EMainCategory InMainCategory, const FString& InSubCategory)
{
	MainCategory = InMainCategory;

	SubCategory = InSubCategory;
}

FActorCategory::FActorCategory(EMainCategory InMainCategory, EArchitectureSubCategory InSubCategory)
{
	UEnum* sub_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EArchitectureSubCategory"), true);
	if (sub_category_enum)
	{
		SubCategory = sub_category_enum->GetNameStringByValue(static_cast<int64>(InSubCategory));
	}
}

FActorCategory::FActorCategory(EMainCategory InMainCategory, EDecorationSubCategory InSubCategory)
{
	UEnum* sub_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDecorationSubCategory"), true);
	if (sub_category_enum)
	{
		SubCategory = sub_category_enum->GetNameStringByValue(static_cast<int64>(InSubCategory));
	}
}

FActorCategory::FActorCategory(EMainCategory InMainCategory, EDeliverySubCategory InSubCategory)
{
	UEnum* sub_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDeliverySubCategory"), true);
	if (sub_category_enum)
	{
		SubCategory = sub_category_enum->GetNameStringByValue(static_cast<int64>(InSubCategory));
	}
}

FActorCategory::FActorCategory(EMainCategory InMainCategory, EFoodSubCategory InSubCategory)
{
	UEnum* sub_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EFoodSubCategory"), true);
	if (sub_category_enum)
	{
		SubCategory = sub_category_enum->GetNameStringByValue(static_cast<int64>(InSubCategory));
	}
}

FActorCategory::FActorCategory(EMainCategory InMainCategory, EKitchenSubCategory InSubCategory)
{
	UEnum* sub_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EKitchenSubCategory"), true);
	if (sub_category_enum)
	{
		SubCategory = sub_category_enum->GetNameStringByValue(static_cast<int64>(InSubCategory));
	}
}

FActorCategory::FActorCategory(EMainCategory InMainCategory, ERestaurantSubCategory InSubCategory)
{
	UEnum* sub_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERestaurantSubCategory"), true);
	if (sub_category_enum)
	{
		SubCategory = sub_category_enum->GetNameStringByValue(static_cast<int64>(InSubCategory));
	}
}

FString FActorCategory::GetFullCategory()
{
	// Get string representation of the main category
	UEnum* main_category_enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMainCategory"), true);
	if (main_category_enum)
	{
		return main_category_enum->GetNameStringByValue(static_cast<int64>(MainCategory)) + "::" + SubCategory;
	}
	return FString();
}