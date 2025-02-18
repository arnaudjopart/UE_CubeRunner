// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelChunck.generated.h"

UCLASS()
class CUBERUNNER_API ALevelChunck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelChunck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Length = 10000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveSpeed;

};
