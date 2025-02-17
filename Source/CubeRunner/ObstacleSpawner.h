// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class CUBERUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	UFUNCTION()
	void StartSpawn();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> SpawnPositions;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> ObstaclesCollection;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
