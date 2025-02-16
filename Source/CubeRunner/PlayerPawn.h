// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePawnBase.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */

UCLASS()
class CUBERUNNER_API APlayerPawn : public AGamePawnBase
{
	GENERATED_BODY()

public:
	void Tick(float DeltaSeconds) override;
	void Move(float Value);
	void Jump();
	UPROPERTY(VisibleAnywhere, Category = Movement)
	int CurrentMovePositionIndex;
	UPROPERTY(EditAnywhere, Category = Movement)
	float StepDistance;
	UPROPERTY(EditAnywhere, Category = Movement)
	float MoveSpeed;
};
