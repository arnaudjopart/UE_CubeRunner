// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChunck.h"


// Sets default values
ALevelChunck::ALevelChunck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelChunck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelChunck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	Location.X-=MoveSpeed*DeltaTime;
	SetActorLocation(Location);
	if(Location.X<-(Length+Offset))
	{
		Destroy();
	}
}

