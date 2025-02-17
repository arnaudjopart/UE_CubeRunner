// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "SAdvancedRotationInputBox.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector PlayerLocation = GetActorLocation();
	FVector TargetPosition = FVector(PlayerLocation.X, CurrentMovePositionIndex*StepDistance, PlayerLocation.Z);
	FVector NextPosition = FMath::Lerp(PlayerLocation, TargetPosition, DeltaSeconds*MoveSpeed);
	SetActorLocation(NextPosition);
	
}

void APlayerPawn::Move(float Value)
{
	
	if (Value > 0)
	{
		CurrentMovePositionIndex++;
		CurrentMovePositionIndex = FMath::Min(1, CurrentMovePositionIndex);
	}else if (Value<0)
	{
		CurrentMovePositionIndex--;
		CurrentMovePositionIndex = FMath::Max(-1, CurrentMovePositionIndex);
	}
}

void APlayerPawn::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerPawn::Jump"));
}

void APlayerPawn::ProcessDamage()
{
	Health--;
	UE_LOG(LogTemp, Warning, TEXT("PlayerPawn::ProcessDamage - %d"),Health);
	if(Health<=0)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		//GameMode->EndPlay(EEndPlayReason::Destroyed);
	}
	OnPlayerLivesChangedEvent.Broadcast(Health);
}
