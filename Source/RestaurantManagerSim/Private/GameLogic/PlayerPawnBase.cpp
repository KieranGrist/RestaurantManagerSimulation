// Fill out your copyright notice in the Description page of Project Settings.
#include "GameLogic/PlayerPawnBase.h"
#include "Actors/InteractableActorBase.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
    CreateEditorModeActorsMap();
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawnBase::CreateEditorModeActorsMap()
{
    EditorModeActorsMap.Empty();

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
        const FActorCategory& actor_category = default_actor->GetActorCategory();

        // Add the actor class to the map under its category
        FEditorModeActors& spawnable_actors = EditorModeActorsMap.FindOrAdd(actor_category);

        FEditorModeActorBase new_actor_Type = FEditorModeActorBase();

        new_actor_Type.ActorSpawnClass = actor_class;

        spawnable_actors.MappedClasses.Add(actor_class->GetName(), new_actor_Type);
    }

    EditorModeActorsMap.KeySort([](const FActorCategory& A, const FActorCategory& B) 
        {
            if (A.GetMainCategory() < B.GetMainCategory())
                return true;

            if (A.GetMainCategory() > B.GetMainCategory())
                return false;

            if (A.GetSubCategory() < B.GetSubCategory())
                return true;

            if (A.GetSubCategory() > B.GetSubCategory())
                return false;
            return false;
     });
}
