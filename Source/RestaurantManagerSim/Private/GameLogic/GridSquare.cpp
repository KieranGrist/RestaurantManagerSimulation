// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLogic/GridSquare.h"

// Sets default values
AGridSquare::AGridSquare()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the GridCollision component and attach it to the root
	GridSquareMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSquareMesh"));
	RootComponent = GridSquareMesh;

	// Set default box extent (size)
	GridSquareMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GridSquareMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GridSquareMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GridSquareMesh->SetGenerateOverlapEvents(true);
	GridSquareMesh->SetNotifyRigidBodyCollision(true);

	// Create the GridCollision component and attach it to the root
	GridCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GridCollision"));
	GridCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Set default box extent (size)
	GridCollision->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	GridCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GridCollision->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GridCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GridCollision->SetGenerateOverlapEvents(true);
	GridCollision->SetNotifyRigidBodyCollision(true);
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

void AGridSquare::NotifyActorBeginOverlap(AActor* InOtherActor)
{
	Super::NotifyActorBeginOverlap(InOtherActor);
	HandleActorCollision(InOtherActor);
}

void AGridSquare::NotifyActorEndOverlap(AActor* InOtherActor)
{
	Super::NotifyActorEndOverlap(InOtherActor);
	HandleActorCollision(InOtherActor);
}

void AGridSquare::NotifyHit(UPrimitiveComponent* InMyComp, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, bool InSelfMoved, FVector InHitLocation, FVector InHitNormal, FVector InNormalImpulse, const FHitResult& InHit)
{
	Super::NotifyHit(InMyComp, InOtherActor, InOtherComp, InSelfMoved, InHitLocation, InHitNormal, InNormalImpulse, InHit);
	HandleActorCollision(InOtherActor);
}

void AGridSquare::OnEditMode(bool IsInEditMode)
{
	UpdateMaterial();

	if (!IsInEditMode)
		UnsnapActor();
	SnapActorToGrid(EditModeGridActor);
	EditModeGridActor = nullptr;
}

bool AGridSquare::IsActorClassOnIgnoreList(const TSubclassOf<AActor>& InClass) const
{
	return ActorsToIgnore.Find(InClass) != INDEX_NONE;
}
void AGridSquare::HandleActorCollision(AActor* InGridActor)
{
	if (InGridActor == this || InGridActor == GridActor || IsActorClassOnIgnoreList(InGridActor->GetClass()))
		return;
	SnapActorToGrid(InGridActor);
}

void AGridSquare::SetGridManager(AGridManager* InGridManager)
{
	GridManager = InGridManager;
	GridManager->OnEditModeDelegate.AddDynamic(this, &AGridSquare::OnEditMode);
}

AGridManager* AGridSquare::GetGridManager() const
{
	return GridManager;
}

bool AGridSquare::IsGridOccupied() const
{
	return IsValid(GridActor);
}

void AGridSquare::RotateGridActorLeft()
{
	GridActor->SetActorRotation(GetActorRotation() + FRotator(0, 90, 0));
}

void AGridSquare::RotateGridActorRight()
{
	GridActor->SetActorRotation(GetActorRotation() + FRotator(0, -90, 0));
}

void AGridSquare::SnapActorToGrid(AActor* InOtherActor)
{
	if (!InOtherActor)
	{
		UnsnapActor();
		EditModeGridActor = nullptr;
		GridActor = nullptr;
		return;
	}

	// Grid Actors spawn in detached, when the player moves them with any system they are "popped" up and detached, if they are attached it means we have an actor which is larger then one grid!
	if (InOtherActor->GetAttachParentActor())
		return;

	InOtherActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if (GridManager->IsInEditMode)
	{
		InOtherActor->SetActorRelativeLocation(EditModeSnapOffset);
		EditModeGridActor = InOtherActor;
	}
	else
	{
		InOtherActor->SetActorRelativeLocation(ActorSnapOffset);
		GridActor = InOtherActor;
	}
}

void AGridSquare::UnsnapActor()
{
	GridActor->SetActorRelativeLocation(EditModeSnapOffset);
	GridActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AGridSquare::MoveActor(EGridSquareDirection InDirection)
{
	AGridSquare* to = GetNeighbourSquare(InDirection);

	if (!to || !GridManager)
		return;

	GridManager->MoveGridActor(GridActor, this, to);
}

AGridSquare* AGridSquare::GetNeighbourSquare(EGridSquareDirection InNeighbourDirection) const
{
	return *NeighbourSquares.Find(InNeighbourDirection);
}

void AGridSquare::UpdateNeighbours()
{
	TMap<EGridSquareDirection, FGridLocation> neighbour_locations =
	{
		{EGridSquareDirection::North, FGridLocation(GridSquareLocation.Row + 1,GridSquareLocation.Column)},
		{EGridSquareDirection::East,  FGridLocation(GridSquareLocation.Row,GridSquareLocation.Column +1)},
		{EGridSquareDirection::South, FGridLocation(GridSquareLocation.Row - 1,GridSquareLocation.Column)},
		{EGridSquareDirection::West,  FGridLocation(GridSquareLocation.Row,GridSquareLocation.Column -1)}
	};

	for (auto location_pair : neighbour_locations)
	{
		SetNeighbourSquare(location_pair.Key, GridManager->GetGridSquare(location_pair.Value));
	}
}

void AGridSquare::SetNeighbourSquare(EGridSquareDirection InGridSquareDirection, AGridSquare* InGridActor)
{
	NeighbourSquares.Add(InGridSquareDirection, InGridActor);
}

void AGridSquare::SetGridSquareLocation(const FGridLocation& InGridLocation)
{
	GridSquareLocation = InGridLocation;
}

const FGridLocation& AGridSquare::GetGridSquareLocation()
{
	return GridSquareLocation;
}

void AGridSquare::UpdateMaterial()
{
	UMaterialInstanceDynamic* dynamic_material_instance = nullptr;
	// Create a dynamic material instance
	if (GridManager->IsInEditMode)
	{
		dynamic_material_instance = UMaterialInstanceDynamic::Create(GridEditMaterial, GridSquareMesh);


		if (GridSquareLocation.Row % 2 == 0 || GridSquareLocation.Row == 0)
		{
			dynamic_material_instance->SetVectorParameterValue(FName("Color"), GridEditColor1);
		}
		else
		{
			dynamic_material_instance->SetVectorParameterValue(FName("Color"), GridEditColor2);
		}
	}
	else
		dynamic_material_instance = UMaterialInstanceDynamic::Create(FloorMaterial, GridSquareMesh);

	// Apply the dynamic material instance to the mesh
	GridSquareMesh->SetMaterial(0, dynamic_material_instance);
}
