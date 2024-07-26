// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameLogic/GridManager.h"
#include "GridSquare.generated.h"

UENUM(BlueprintType)
enum class EGridSquareDirection : uint8
{
	North UMETA(DisplayName = "North"),
	East UMETA(DisplayName = "East"),
	South UMETA(DisplayName = "South"),
	West UMETA(DisplayName = "West")
};
class AInteractableActorBase;

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

	bool IsActorClassOnIgnoreList(const TSubclassOf<AInteractableActorBase>& InClass) const;

	void HandleActorCollision(AInteractableActorBase* InOtherActor);

	template<class T>
	T* GetGridActor() const
	{
		// Ensure that T is derived from AActor
		static_assert(TIsDerivedFrom<T, AInteractableActorBase>::IsDerived, "T must be derived from AInteractableActorBase");

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
	void EditorSnapActorToGrid();
		
	void SnapActorToGrid(AInteractableActorBase* InOtherActor);

	void UnsnapActor();

	void MoveActor(EGridSquareDirection InDirection);

	AGridSquare* GetNeighbourSquare(EGridSquareDirection InNeighbourDirection) const;

	UFUNCTION(CallInEditor)
	void UpdateNeighbours();

	void SetNeighbourSquare(EGridSquareDirection InGridSquareDirection, AGridSquare* InGridActor);

	void SetGridSquareLocation(const FGridLocation& InGridLocation);

	void SetIndex(int32 InIndex);

	const FGridLocation& GetGridSquareLocation();

	const FLinearColor& GetEditModeColor() const;

	UFUNCTION(CallInEditor)
	void UpdateMaterial();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EGridSquareDirection, AGridSquare*> NeighbourSquares;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GridSquareMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* GridCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGridManager* GridManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AInteractableActorBase>> ActorsToIgnore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInteractableActorBase* GridActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInteractableActorBase* EditModeGridActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActorSnapped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* EditModeSnapOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ActorSnapOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGridLocation GridSquareLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* EditModeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* FloorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EditModeColorA = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EditModeColorB = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EditModeOccupiedColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EditModePreviewColor = FLinearColor::Yellow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EditModeWallColor = FLinearColor::Blue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Index;
};
