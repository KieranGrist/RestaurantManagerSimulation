// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"


// Sets default values
AInteractableActorBase::AInteractableActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorData = CreateDefaultSubobject<UGameDataAsset>(TEXT("ActorData"));

	// Create and configure the GridSquareMesh component
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSquareMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ActorMesh->SetupAttachment(RootComponent);

	ActorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActorMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	ActorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ActorMesh->SetGenerateOverlapEvents(true);
	ActorMesh->SetNotifyRigidBodyCollision(true); 
}

// Called when the game starts or when spawned
void AInteractableActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const FActorCategory& AInteractableActorBase::GetActorCategory() const
{
	return ActorCategory;
}
