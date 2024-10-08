// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLogic/GridSquare.h"
#include "Actors/InteractableActorBase.h"

// Sets default values
AGridSquare::AGridSquare()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and configure the GridSquareMesh component
	GridSquareMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSquareMesh"));
	RootComponent = GridSquareMesh;

	GridSquareMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GridSquareMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GridSquareMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GridSquareMesh->SetGenerateOverlapEvents(true);
	GridSquareMesh->SetNotifyRigidBodyCollision(true);

	// Create and configure the GridCollision component
	GridCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GridCollision"));
	GridCollision->SetupAttachment(RootComponent);


	// Set default box extent (size)
	GridCollision->InitBoxExtent(FVector(50.0f));  // Ensure the FVector has a float value

	GridCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // Example change; use appropriate value based on your needs
	GridCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);  // Change based on your needs
	GridCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GridCollision->SetGenerateOverlapEvents(true);
	GridCollision->SetNotifyRigidBodyCollision(false);  // Set to false if only overlap events are needed

	EditModeSnapOffset = CreateDefaultSubobject<USceneComponent>(TEXT("EditModeSnapOffset"));
	ActorSnapOffset = CreateDefaultSubobject<USceneComponent>(TEXT("ActorSnapOffset"));

	EditModeSnapOffset->SetupAttachment(RootComponent);
	ActorSnapOffset->SetupAttachment(RootComponent);

	EditModeSnapOffset->SetRelativeLocation(FVector(0, 0, 50));
	ActorSnapOffset->SetRelativeLocation(FVector(0, 0, 100));
}


// Called when the game starts or when spawned
void AGridSquare::BeginPlay()
{
	Super::BeginPlay();
	UpdateMaterial(); 
}

// Called every frame
void AGridSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridSquare::NotifyActorBeginOverlap(AActor* InOtherActor)
{
	Super::NotifyActorBeginOverlap(InOtherActor);
	HandleActorCollision(Cast<AInteractableActorBase>(InOtherActor));
}

void AGridSquare::NotifyActorEndOverlap(AActor* InOtherActor)
{
	Super::NotifyActorEndOverlap(InOtherActor);
	HandleActorCollision(Cast<AInteractableActorBase>(InOtherActor));
}

void AGridSquare::NotifyHit(UPrimitiveComponent* InMyComp, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, bool InSelfMoved, FVector InHitLocation, FVector InHitNormal, FVector InNormalImpulse, const FHitResult& InHit)
{
	Super::NotifyHit(InMyComp, InOtherActor, InOtherComp, InSelfMoved, InHitLocation, InHitNormal, InNormalImpulse, InHit);
	HandleActorCollision(Cast<AInteractableActorBase>(InOtherActor));
}

void AGridSquare::OnEditMode(bool IsInEditMode)
{
	UpdateMaterial();

	if (!IsInEditMode)
		UnsnapActor();
	SnapActorToGrid(EditModeGridActor);
	EditModeGridActor = nullptr;
}

bool AGridSquare::IsActorClassOnIgnoreList(const TSubclassOf<AInteractableActorBase>& InClass) const
{
	return ActorsToIgnore.Find(InClass) != INDEX_NONE;
}
void AGridSquare::HandleActorCollision(AInteractableActorBase* InGridActor)
{
	if (InGridActor == GridActor)
		return;
	if (InGridActor && IsActorClassOnIgnoreList(InGridActor->GetClass()))
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
	if (!GridActor)
		return;
	FRotator current_rotation = GetActorRotation();
	GridActor->SetActorRotation(FRotator(current_rotation.Pitch, current_rotation.Yaw + 90, current_rotation.Roll));
}

void AGridSquare::RotateGridActorRight()
{
	if (!GridActor)
		return;
	FRotator current_rotation = GetActorRotation();
	GridActor->SetActorRotation(FRotator(current_rotation.Pitch, current_rotation.Yaw + -90, current_rotation.Roll));
}

void AGridSquare::EditorSnapActorToGrid()
{
	if (!GridActor)
		return;

	GridActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);;
	GridActor->SetActorRelativeLocation(ActorSnapOffset->GetRelativeLocation());
}

void AGridSquare::SnapActorToGrid(AInteractableActorBase* InOtherActor)
{
	if (!InOtherActor)
	{
		UnsnapActor();
		return;
	}

	// Grid Actors spawn in detached, when the player moves them with any system they are "popped" up and detached, if they are attached it means we have an actor which is larger then one grid!
	if (InOtherActor->GetAttachParentActor() != this)
		return;

	InOtherActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if (GridManager->IsInEditMode)
	{
		InOtherActor->SetActorRelativeLocation(EditModeSnapOffset->GetRelativeLocation());
		EditModeGridActor = InOtherActor;
	}
	else
	{
		InOtherActor->SetActorRelativeLocation(ActorSnapOffset->GetRelativeLocation());
		GridActor = InOtherActor;
	}
}

void AGridSquare::UnsnapActor()
{
	if (EditModeGridActor)
	{
		EditModeGridActor->SetActorRelativeLocation(EditModeSnapOffset->GetRelativeLocation());
		EditModeGridActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EditModeGridActor = nullptr;
	}

	if (GridActor)
	{
		GridActor->SetActorRelativeLocation(EditModeSnapOffset->GetRelativeLocation());
		GridActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GridActor = nullptr;
	}
}

void AGridSquare::MoveActor(EGridSquareDirection InDirection)
{
	if (!GridActor)
		return;

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
		{EGridSquareDirection::East,  FGridLocation(GridSquareLocation.Row,GridSquareLocation.Column + 1)},
		{EGridSquareDirection::South, FGridLocation(GridSquareLocation.Row - 1,GridSquareLocation.Column)},
		{EGridSquareDirection::West,  FGridLocation(GridSquareLocation.Row,GridSquareLocation.Column - 1)}
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

void AGridSquare::SetIndex(int32 InIndex)
{
	Index = InIndex;
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
		dynamic_material_instance = UMaterialInstanceDynamic::Create(EditModeMaterial, GridSquareMesh);
		dynamic_material_instance->SetVectorParameterValue(FName("Color"), GetEditModeColor());
	}
	else
		dynamic_material_instance = UMaterialInstanceDynamic::Create(FloorMaterial, GridSquareMesh);

	// Apply the dynamic material instance to the mesh
	GridSquareMesh->SetMaterial(0, dynamic_material_instance);
}

const FLinearColor& AGridSquare::GetEditModeColor() const
{
	if (GridActor)
		return EditModeOccupiedColor;

	if (EditModeGridActor)
		return EditModePreviewColor;

	if (GridActor && GridActor->GetActorCategory().GetSubCategory().Equals(FActorCategory::EnumToString(EArchitectureSubCategory::Wall)))
		return EditModeWallColor;

	if ((GridSquareLocation.Row + GridSquareLocation.Column) % 2 == 0)
		return EditModeColorA;
	else
		return EditModeColorB;
}
