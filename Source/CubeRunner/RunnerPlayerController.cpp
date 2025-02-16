// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerPawn.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ARunnerPlayerController::ARunnerPlayerController()
{
}

void ARunnerPlayerController::OnScoreChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("Score Changed"));
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
	/*TArray<AActor*> Result;
	UGameplayStatics::GetAllActorsOfClass(this,ACameraActor::StaticClass(),Result);
	if (Result.Num() > 0)
	{
		if (Result[0] != nullptr)
		{
			SetViewTargetWithBlend(Result[0]);
		}
	}*/
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &ARunnerPlayerController::StartGame,StarTimerDuration,false);
	StartTimer(StarTimerDuration);
	OnScoreChangedDelegate.AddDynamic(this,&ARunnerPlayerController::OnScoreChanged);
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

void ARunnerPlayerController::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("ARunnerPlayerController::StartGame"));
	EnableInput(this);
	OnScoreChangedDelegate.Broadcast();
}
