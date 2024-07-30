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
    CreateSpawnableActorsMap();
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

void APlayerPawnBase::CreateSpawnableActorsMap()
{
    SpawnableActorsMap.Empty();

    for (TSubclassOf<AInteractableActorBase> actor_class : UIAvailableActors)
    {
        if (!actor_class)
        {
            continue;
        }

        // Access the class default object (CDO)
        AInteractableActorBase* default_actor = actor_class->GetDefaultObject<AInteractableActorBase>();

        if (!default_actor)
            continue;
        FActorCategory actor_category = default_actor->GetActorCategory();

        // Add the actor class to the map under its category
        FSpawnableActors& spawnable_actors = SpawnableActorsMap.FindOrAdd(actor_category);
        spawnable_actors.MappedClasses.Add(actor_class->GetName(), actor_class);
    }

    //SpawnableActorsMap.KeySort([](const FActorCategory& A, const FActorCategory& B) {
    //    EMainCategory a_main_category;
    //    EMainCategory b_main_category;



    //  //  A.GetCategoriesAsEnums();
    // });
}
