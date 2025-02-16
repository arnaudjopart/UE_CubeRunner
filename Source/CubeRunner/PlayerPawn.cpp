// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "SAdvancedRotationInputBox.h"

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
	UE_LOG(LogTemp, Warning, TEXT("PlayerPawn::Move - %f"),Value);
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
