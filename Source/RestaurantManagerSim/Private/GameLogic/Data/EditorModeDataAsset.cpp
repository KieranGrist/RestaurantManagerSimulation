// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/Data/EditorModeDataAsset.h"
#include "Actors/InteractableActorBase.h"

UEditorModeDataAsset::UEditorModeDataAsset()
{

}

void UEditorModeDataAsset::CreateEditorModeActorsMap()
{
	for (TSubclassOf<AInteractableActorBase> actor_class : EditorModeBPActors)
	{
		if (!actor_class)
		{
			continue;
		}

		// Access the class default object (CDO)
		AInteractableActorBase* default_actor = actor_class->GetDefaultObject<AInteractableActorBase>();

		if (!default_actor)
			continue;

		const FString& actor_category = default_actor->GetActorCategory().GetFullCategory();
		
		// Add the actor class to the map under its category
		FEditorModeActors& spawnable_actors = EditorModeActorsMap.FindOrAdd(actor_category);
		if(spawnable_actors.MappedClasses.Find(actor_class->GetName()))
			continue;

		spawnable_actors.MappedClasses.Add(actor_class->GetName(), FEditorModeActorBase(actor_class));
	}

	EditorModeActorsMap.KeySort([](const FString& A, const FString& B)
		{
			FString main_category_a = FActorCategory::GetMainCategory(A);
			FString main_category_b = FActorCategory::GetMainCategory(B);
			FString sub_category_a = FActorCategory::GetSubCategory(A);
			FString sub_category_b = FActorCategory::GetSubCategory(B);

			if (main_category_a < main_category_b)
				return true;

			if (main_category_a > main_category_b)
				return false;

			if (sub_category_a < sub_category_b)
				return true;

			if (sub_category_a > sub_category_b)
				return false;
			return false;
		});
}

