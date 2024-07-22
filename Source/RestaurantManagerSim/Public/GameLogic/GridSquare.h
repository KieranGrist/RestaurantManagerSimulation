// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameLogic/GridManager.h"
#include "GridSquare.generated.h"

UENUM(BlueprintType)
enum class GridSquareDirection : uint8
{
	North UMETA(DisplayName = "North"),
	East UMETA(DisplayName = "East"),
	South UMETA(DisplayName = "South"),
	West UMETA(DisplayName = "West")
};

UCLASS()
class RESTAURANTMANAGERSIM_API AGridSquare : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridSquare();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* InOtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* InOtherActor) override;

	virtual void NotifyHit(UPrimitiveComponent* InMyComp, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, bool InSelfMoved, FVector InHitLocation, FVector InHitNormal, FVector InNormalImpulse, const FHitResult& InHit) override;

	UFUNCTION()
	void OnEditMode(bool IsInEditMode);

	bool IsActorClassOnIgnoreList(const TSubclassOf<AActor>& InClass) const;

	void HandleActorCollision(AActor* InOtherActor);
	
	template<class T>
	T* GetGridActor() const
	{
		// Ensure that T is derived from AActor
		static_assert(TIsDerivedFrom<T, AActor>::IsDerived, "T must be derived from AActor");

		return Cast<T>(GridActor);
	}
	
	void SetGridManager(AGridManager* InGridManager);

	AGridManager* GetGridManager() const;

	bool IsGridOccupied() const;

	// Rotate the grid actor by 90 degrees left
	UFUNCTION(CallInEditor)
	void RotateGridActorLeft();

	// Rotate the grid actor by 90 degrees right
	UFUNCTION(CallInEditor)
	void RotateGridActorRight();

	UFUNCTION(CallInEditor)
	void SnapActorToGrid(AActor* InOtherActor);

	void UnsnapActor();

	void MoveActor(GridSquareDirection InDirection);
	
	AGridSquare* GetNeighbourSquare(GridSquareDirection InNeighbourDirection) const;

	void UpdateNeighbours();
	
	void SetNeighbourSquare(GridSquareDirection InGridSquareDirection, AGridSquare* InGridActor);

	void SetGridSquareLocation(const FGridLocation& InGridLocation);

	const FGridLocation& GetGridSquareLocation();

	void UpdateMaterial();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<GridSquareDirection, AGridSquare*> NeighbourSquares;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GridSquareMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* GridCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGridManager* GridManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> ActorsToIgnore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* GridActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* EditGridActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActorSnapped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EditModeSnapOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ActorSnapOffset = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGridLocation GridSquareLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* GridEditMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* FloorMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor GridEditColor1 = FLinearColor::Black;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor GridEditColor2 = FLinearColor::White;
};
