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
	MainCategory = FActorCategory::GetEnumNameString(EMainCategory::Error);

	SubCategory = "";
	FullCategory = "";
}
const FString& FActorCategory::GetFullCategory() const
{
	return FullCategory;
}
const FString& FActorCategory::GetMainCategory() const
{
	return MainCategory;
}
const FString& FActorCategory::GetSubCategory() const
{
	return SubCategory;
}

// Template constructor implementation
template <typename TSubCategoryEnum>
FActorCategory::FActorCategory(EMainCategory InMainCategory, TSubCategoryEnum InSubCategory)
{
	MainCategory = FActorCategory::GetEnumNameString(InMainCategory);
	SubCategory = FActorCategory::GetEnumNameString(InSubCategory);
	FullCategory = MainCategory + "::" + SubCategory;
}

template<typename TEnum>
FString GetEnumNameString(TEnum InEnum)
{
	// Ensure TEnum is a UEnum type
	const UEnum* enum_ptr = TEnum::StaticEnum();
	if (!enum_ptr)
	{
		// Log an error or return an empty string if the enum is not found
		return TEXT("Error: Enum not found");
	}

	// Get the string representation of the enum value
	return enum_ptr->GetNameStringByValue(static_cast<int64>(InEnum));
}
