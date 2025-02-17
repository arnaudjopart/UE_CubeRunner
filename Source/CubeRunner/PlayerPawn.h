// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePawnBase.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLivesChangedSignature, int32, NewScore);

UCLASS()
class CUBERUNNER_API APlayerPawn : public AGamePawnBase
{
	GENERATED_BODY()


public:
	void Tick(float DeltaSeconds) override;
	void Move(float Value);
	void Jump();
	void ProcessDamage();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();
	UPROPERTY(BlueprintAssignable)
	FOnPlayerLivesChangedSignature OnPlayerLivesChangedEvent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	int CurrentMovePositionIndex;
	UPROPERTY(EditAnywhere, Category = Movement)
	float StepDistance;
	UPROPERTY(EditAnywhere, Category = Movement)
	float MoveSpeed;
	UPROPERTY(EditAnywhere, Category = "Stats", BlueprintReadOnly)
	int Health =5;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera Shakes")
	TSubclassOf<UCameraShakeBase> CameraShake;
};
