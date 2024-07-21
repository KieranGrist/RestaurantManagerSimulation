// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/GridSquare.h"

// Sets default values
AGridSquare::AGridSquare()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Create the GridCollision component and attach it to the root
    GridCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GridCollision"));
    RootComponent = GridCollision;

    // Set default box extent (size)
    GridCollision->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	GridCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GridCollision->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GridCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GridCollision->SetGenerateOverlapEvents(true);
	GridCollision->SetNotifyRigidBodyCollision(true);

    // Set collision properties if needed
    GridCollision->SetCollisionProfileName(TEXT("BlockAll"));

}

// Called when the game starts or when spawned
void AGridSquare::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridSquare::NotifyHit(UPrimitiveComponent* InMyComp, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, bool InSelfMoved, FVector InHitLocation, FVector InHitNormal, FVector InNormalImpulse, const FHitResult& InHit)
{
	Super::NotifyHit(InMyComp, InOtherActor, InOtherComp, InSelfMoved, InHitLocation, InHitNormal, InNormalImpulse, InHit);

	if (!InOtherActor || InOtherActor == this || InOtherActor == GridActor || IsActorClassOnIgnoreList(InOtherActor->GetClass()))
		return;

	SetGridActor(InOtherActor);
}

bool AGridSquare::IsActorClassOnIgnoreList(const TSubclassOf<AActor>& InClass) const
{
	return ActorsToIgnore.Find(InClass) != INDEX_NONE;
}

void AGridSquare::SetGridActor(AActor* InGridActor)
{
	GridActor = InGridActor;
}

bool AGridSquare::IsGridOccupied() const
{
	return IsValid(GridActor);
}

template<typename T>
T* AGridSquare::GetGridActor() const
{
	// Ensure that T is derived from AActor
	static_assert(TIsDerivedFrom<T, AActor>::IsDerived, "T must be derived from AActor");

	return Cast<T>(GridActor);
}

// Ensure the template function is instantiated for the necessary types
template AActor* AGridSquare::GetGridActor<AActor>() const;