// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameLogic/GameData.h"
#include "EditModeUIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RESTAURANTMANAGERSIM_API UEditModeUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEditModeUIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <TSubclassOf<class AInteractableActorBase>> UIAvailableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FActorCategory, FSpawnableActors> SpawnableActorsMap;
};
