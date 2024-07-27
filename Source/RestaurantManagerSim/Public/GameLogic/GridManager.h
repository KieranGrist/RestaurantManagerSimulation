#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogic/GameData.h"
#include "GridManager.generated.h"

class AGridSquare;
class AInteractableActorBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditMode, bool, IsInEditMode);

USTRUCT(BlueprintType)
struct FGridLocation
{
	GENERATED_BODY()
	public:
	FGridLocation() { Row = 0; Column = 0; }
	FGridLocation(int32 InRow, int32 InColumn) { Row = InRow;  Column = InColumn; }

	// Equality operator
	bool operator==(const FGridLocation& Other) const
	{
		return Row == Other.Row && Column == Other.Column;
	}

	// Inequality operator
	bool operator!=(const FGridLocation& Other) const
	{
		return !(*this == Other);
	}

	// Less than operator
	bool operator<(const FGridLocation& Other) const
	{
		if (Row < Other.Row)
		{
			return true;
		}
		if (Row == Other.Row && Column < Other.Column)
		{
			return true;
		}
		return false;
	}

	// Greater than operator
	bool operator>(const FGridLocation& Other) const
	{
		if (Row > Other.Row)
		{
			return true;
		}
		if (Row == Other.Row && Column > Other.Column)
		{
			return true;
		}
		return false;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column = 0;
};

inline uint32 GetTypeHash(const FGridLocation& Location)
{
	return HashCombine(::GetTypeHash(Location.Row), ::GetTypeHash(Location.Column));
}

UCLASS()
class RESTAURANTMANAGERSIM_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	AGridManager();

	// Initialize the grid with specified dimensions
	UFUNCTION(CallInEditor)
	void InitializeGrid();

	void InitializeGrid(int32 InRows, int32 InColumns);

	// Get the grid square at the specified position
	AGridSquare* GetGridSquare(const FGridLocation& InGridLocation) const;

	AGridSquare* CreateGridSquare();

	UFUNCTION(CallInEditor)
	void StartEditMode();

	UFUNCTION(CallInEditor)
	void StopEditMode();

	UPROPERTY(BlueprintAssignable)
	FOnEditMode OnEditModeDelegate;

	// Move an actor from one grid square to another
	void MoveGridActor(AInteractableActorBase* InActor, AGridSquare* InFromGridSquare, AGridSquare* InToGridSquare);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInEditMode = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Columns = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGridLocation, AGridSquare*> GridSquares;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGridSquare> GridSquareClass;
};
