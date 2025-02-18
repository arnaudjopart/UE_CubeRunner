// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "RunnerPlayerController.h"
#include "SAdvancedRotationInputBox.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const FVector PlayerLocation = GetActorLocation();
	const FVector TargetPosition = FVector(PlayerLocation.X, CurrentMovePositionIndex*StepDistance, PlayerLocation.Z);
	const FVector NextPosition = FMath::Lerp(PlayerLocation, TargetPosition, DeltaSeconds*MoveSpeed);
	SetActorLocation(NextPosition);
	
}

void APlayerPawn::Move(float Value)
{
	if (MoveSound!= nullptr) UGameplayStatics::PlaySoundAtLocation(this,MoveSound,GetActorLocation());
	if (CameraShake!=nullptr) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShake);
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
	if (CameraShake!=nullptr) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShake);
	if(Health<=0)
	{
		Cast<ARunnerPlayerController>(GetController())->EndGame();
	}else
	{
		OnPlayerLivesChangedEvent.Broadcast(Health);
		OnHit();
	}
	
}
