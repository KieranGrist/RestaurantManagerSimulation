// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GridSquare.generated.h"

UCLASS()
class RESTAURANTMANAGERSIM_API  AGridSquare : public AActor
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

	bool IsActorClassOnIgnoreList(const TSubclassOf<AActor>& InClass) const;

	void SetGridActor(AActor* InGridActor);

	bool IsGridOccupied() const;

	template<class T>
	T* GetGridActor() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* GridCollision;

protected:
	/* Not all Actors on the Grid are going to be an interactable Actor so instead we are going to store it as an Actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* GridActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> ActorsToIgnore;
};

