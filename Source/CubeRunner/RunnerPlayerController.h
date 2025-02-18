// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "PlayerPawn.h"
#include "RunnerPlayerController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature,float,Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartGame,float,StartTimerLenght);

UCLASS()
class CUBERUNNER_API ARunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARunnerPlayerController();
	
protected:
	virtual void BeginPlay() override;
	void MovePlayer(const FInputActionValue& ActionValue);
	void JumpPlayer();
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartTimer(float TimerDuration);


	UPROPERTY(EditAnywhere)
	UInputAction* MoveInpuAction;
	UPROPERTY(EditAnywhere)
	UInputAction* JumpInputAction;
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere)
	ACameraActor* CameraActor;
	//UFUNCTION()
	void StartGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StarTimerDuration=5;

private:
	APlayerPawn* PlayerPawn;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnScoreChangedSignature OnScoreChangedDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimerStartSignature OnTimerStartDelegate;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStartGame OnStartGame;
	int Score;

	void AddPointToScore();
	void EndGame(AActor* Actor);
};
