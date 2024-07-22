// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/GridManager.h"
#include "GameLogic/GridSquare.h"

AGridManager::AGridManager()
{

}

void AGridManager::InitializeGrid()
{
	InitializeGrid(Rows, Columns);
}

void AGridManager::InitializeGrid(int32 InRows, int32 InColumns)
{
	FVector location = FVector::ZeroVector;

	for (auto square_pair : GridSquares)
	{
		square_pair.Value->Destroy();
	}
	GridSquares.Empty();

	// Initialize neighbors for each grid square
	FGridLocation grid_location;
	int32 index = 1;
	for (grid_location.Row = 1; grid_location.Row <= Rows; ++grid_location.Row)
	{
		for (grid_location.Column = 1; grid_location.Column <= Columns; ++grid_location.Column)
		{
			// Increment index
			index++;

			// Create and initialize the grid square
			AGridSquare* grid_square = CreateGridSquare();
			grid_square->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			grid_square->SetActorRelativeLocation(location);
			grid_square->SetGridSquareLocation(grid_location);
			GridSquares.Add(grid_location, grid_square);
			grid_square->SetIndex(index);
			grid_square->UpdateMaterial();

			// Move the location for the next column
			location.Y += 100; // Assuming 100 units is the size of each grid square
		}

		// Reset location.Y for the next row and move location.X for the next row
		location.Y = 0;
		location.X += 100; // Assuming 100 units is the spacing between columns
	}

	for (auto square_pair : GridSquares)
	{
		square_pair.Value->UpdateNeighbours();
	}
}

AGridSquare* AGridManager::GetGridSquare(const FGridLocation& InGridLocation) const
{
	auto found_grid_square = GridSquares.Find(InGridLocation);

	if (found_grid_square)
	{
		return *found_grid_square;
	}
	else
	{
		// Handle the case where the grid square is not found
		UE_LOG(LogTemp, Warning, TEXT("GetGridSquare: No grid square found at location (%d, %d)"), InGridLocation.Row, InGridLocation.Column);
		return nullptr;
	}
}

AGridSquare* AGridManager::CreateGridSquare()
{
	UWorld* world = GetWorld();

	// Ensure the world is valid
	if (!world || !GridSquareClass)
		return nullptr;

	// Set spawn parameters
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Spawn the actor
	AGridSquare* new_grid_square = world->SpawnActor<AGridSquare>(GridSquareClass, GetActorLocation(), GetActorRotation(), spawn_params);
	new_grid_square->SetGridManager(this);
	return new_grid_square;
}

void AGridManager::StartEditMode()
{
	IsInEditMode = true;
	OnEditModeDelegate.Broadcast(IsInEditMode);
}

void AGridManager::StopEditMode()
{
	IsInEditMode = false;
	OnEditModeDelegate.Broadcast(IsInEditMode);
}

void AGridManager::MoveGridActor(AActor* InActor, AGridSquare* InFromGridSquare, AGridSquare* InToGridSquare)
{
	InFromGridSquare->UnsnapActor();
	InToGridSquare->SnapActorToGrid(InActor);
}
