// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawnBase.h"

// Sets default values
AGamePawnBase::AGamePawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

}

void AGamePawnBase::ProcessActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AGamePawnBase::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

void AGamePawnBase::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called when the game starts or when spawned
void AGamePawnBase::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this,&AGamePawnBase::ProcessActorHit);
	OnActorBeginOverlap.AddDynamic(this,&AGamePawnBase::ProcessActorBeginOverlap);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this,&AGamePawnBase::ComponentBeginOverlap);
}

// Called every frame
void AGamePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGamePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

