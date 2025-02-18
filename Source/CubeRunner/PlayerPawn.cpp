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
	FVector NextPosition = FMath::Lerp(PlayerLocation, TargetPosition, DeltaSeconds*MoveSpeed);

	if(IsJumping)
	{
		UE_LOG(LogTemp, Display, TEXT("Jumping"));
		NextPosition.Z+=VerticalSpeed*DeltaSeconds;
		float AppliedGravity = JumpGravity;
		if(VerticalSpeed<0) AppliedGravity*=FallGravityMultiplier;
		VerticalSpeed-= AppliedGravity*DeltaSeconds;
		if(NextPosition.Z<32 && VerticalSpeed<0)
		{
			UE_LOG(LogTemp, Display, TEXT("Stop Jump"));
			IsJumping = false;
			NextPosition.Z=32;
		}
	}
	

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
	if(IsJumping==true) return;
	UE_LOG(LogTemp, Display, TEXT("Jump"));
	IsJumping = true;
	VerticalSpeed = FMath::Sqrt(JumpHeight*2*JumpGravity);
}

void APlayerPawn::ProcessDamage()
{
	Health--;
	if (CameraShake!=nullptr) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShake);
	if(Health<=0)
	{
		Cast<ARunnerPlayerController>(GetController())->EndGame(this);
	}else
	{
		OnPlayerLivesChangedEvent.Broadcast(Health);
		OnHit();
	}
	
}
