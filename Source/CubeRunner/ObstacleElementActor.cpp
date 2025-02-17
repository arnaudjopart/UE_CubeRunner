// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleElementActor.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

AObstacleElementActor::AObstacleElementActor()
{
}

void AObstacleElementActor::ReactToComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReactToComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	if(APlayerPawn* RunnerPlayer = Cast<APlayerPawn>(OtherActor); RunnerPlayer != nullptr)
	{
		RunnerPlayer->ProcessDamage();
	}
}

void AObstacleElementActor::ReactToComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ReactToComponentOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(APlayerPawn* RunnerPlayer = Cast<APlayerPawn>(OtherActor); RunnerPlayer != nullptr)
	{
		RunnerPlayer->ProcessDamage();
	}
}

void AObstacleElementActor::ApplyPoint()
{
	CurrentController->AddPointToScore();
}

void AObstacleElementActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
