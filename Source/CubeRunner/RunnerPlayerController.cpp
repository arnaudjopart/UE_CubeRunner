// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerPawn.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/GameModeBase.h"

ARunnerPlayerController::ARunnerPlayerController()
{
}

void ARunnerPlayerController::RestartGame()
{
	FName PlayerName = FName("TestLevel");
	UGameplayStatics::OpenLevel(this,PlayerName);
	//RestartLevel();
}

void ARunnerPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	FTimerHandle TimeHandler;
	GetWorld()->GetTimerManager().SetTimer(TimeHandler, this, &ARunnerPlayerController::RestartGame,5);
}


void ARunnerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerPawn>(GetPawn());
	
	if ( PlayerPawn == nullptr)	{UE_LOG(LogTemp, Warning, TEXT("ARunnerPlayerController::BeginPlay - No Player Pawn"));}
	else
	{
		DisableInput(this);
	}

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(this,"MainCamera",OutActors);
	if (OutActors.Num()>0)
	{
		if (OutActors[0]!=nullptr) MainCameraActor = OutActors[0];
	}
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &ARunnerPlayerController::StartGame,StarTimerDuration,false);
	StartTimer(StarTimerDuration);
	OnStartGame.Broadcast(5);
}

void ARunnerPlayerController::MovePlayer(const FInputActionValue& ActionValue)
{
	float Value = ActionValue.Get<float>(); 
	PlayerPawn->Move(Value);
}

void ARunnerPlayerController::JumpPlayer()
{
	PlayerPawn->Jump();
}

void ARunnerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext!=nullptr)
			{
				InputSystem->AddMappingContext(InputMappingContext,0);
				if (UEnhancedInputComponent* EIC =Cast<UEnhancedInputComponent>(InputComponent); EIC!=nullptr)
				{
					EIC->BindAction(MoveInpuAction,ETriggerEvent::Started,this,&ARunnerPlayerController::MovePlayer);
					EIC->BindAction(JumpInputAction,ETriggerEvent::Started,this,&ARunnerPlayerController::JumpPlayer);
				}
			}
		}
	}
}

void ARunnerPlayerController::AddPointToScore()
{
	Score++;
	UE_LOG(LogTemp,Display,TEXT("ARunnerPlayerController::AddPointToScore"))
	OnScoreChangedDelegate.Broadcast(Score);
}

void ARunnerPlayerController::EndGame(AActor* Actor)
{
	Actor->Destroy();
	TArray<AActor*> OutActors;
	//if (OutActors[0]!=nullptr)	SetViewTargetWithBlend(MainCameraActor);
	
	GameHasEnded(MainCameraActor,0);
}

void ARunnerPlayerController::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("ARunnerPlayerController::StartGame"));
	EnableInput(this);
	OnTimerStartDelegate.Broadcast();
}
