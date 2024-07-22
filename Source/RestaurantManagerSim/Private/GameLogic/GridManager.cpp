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
	for (grid_location.Row = 0; grid_location.Row < Rows; ++grid_location.Row)
	{
		for (grid_location.Column = 0; grid_location.Column < Columns; ++grid_location.Column)
		{
			AGridSquare* grid_square = CreateGridSquare();
			grid_square->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			grid_square->SetActorRelativeLocation(location);
			grid_square->SetGridSquareLocation(grid_location);
			GridSquares.Add(grid_location, grid_square);
			location.X += 100;
		}
		location.X = 0;
		location.Y += 100;
	}

	for (auto square_pair : GridSquares)
	{
		square_pair.Value->UpdateNeighbours();
	}
}

AGridSquare* AGridManager::GetGridSquare(const FGridLocation& InGridLocation) const
{
	return *GridSquares.Find(InGridLocation);
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
	OnEditModeDelegate.broadcast(IsInEditMode);
}

void AGridManager::StopEditMode()
{
	IsInEditMode = false;
	OnEditModeDelegate.broadcast(IsInEditMode);
}

void AGridManager::MoveGridActor(AActor* InActor, AGridSquare* InFromGridSquare, AGridSquare* InToGridSquare)
{
	InFromGridSquare->UnsnapActor();
	InFromGridSquare->UpdateGridActor(nullptr);
	
	InToGridSquare->UpdateGridActor(InActor);
	InToGridSquare->SnapActorToGrid();
}
