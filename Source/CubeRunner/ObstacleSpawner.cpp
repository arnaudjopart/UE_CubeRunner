// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

#include "RunnerPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AObstacleSpawner::StartSpawn(){

    UE_LOG(LogTemp, Display, TEXT("AObstacleSpawner::StartSpawn"))
}
	
	
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this,0);

	if(ARunnerPlayerController* RunnerPlayerController = Cast<ARunnerPlayerController>(Controller);RunnerPlayerController!=nullptr)
	{
		RunnerPlayerController->OnTimerStartDelegate.AddDynamic(this, &AObstacleSpawner::StartSpawn);
	}
	
	
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

