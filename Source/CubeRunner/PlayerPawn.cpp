// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "RunnerPlayerController.h"
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
		if(NextPosition.Z<FloorHeight && VerticalSpeed<0)
		{
			OnJumpEnd();
			IsJumping = false;
			NextPosition.Z=FloorHeight;
		}
	}
	

	SetActorLocation(NextPosition);
	
	
}

void APlayerPawn::Move(float Value)
{
	if (AllowsMovement==false) return;
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

void APlayerPawn::Jump(float MaxHeight, float GroundHeight)
{
	if(IsJumping==true) return;
	OnJumpSart();
	FloorHeight = GroundHeight;
	UE_LOG(LogTemp, Display, TEXT("Jump"));
	IsJumping = true;
	VerticalSpeed = FMath::Sqrt(MaxHeight*2*JumpGravity);
}

void APlayerPawn::Jump()
{
	if(IsJumping==true) return;
	OnJumpSart();
	FloorHeight = 32;
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

void APlayerPawn::EnableMovement(bool Bool)
{
	AllowsMovement=Bool;
}