// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElementBase.h"

#include "RunnerPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameElementBase::AGameElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = Mesh;

}

void AGameElementBase::SetSpeed(float SpawnSpeed)
{
	Speed= SpawnSpeed; 
}

void AGameElementBase::ReactToComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void AGameElementBase::ReactToComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("AGameElementBase::ReactToComponentOverlap: %s"),*OtherActor->GetActorNameOrLabel())
}

// Called when the game starts or when spawned
void AGameElementBase::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AGameElementBase::ReactToComponentHit);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AGameElementBase::ReactToComponentOverlap);
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this,0);
	if(ARunnerPlayerController* RunnerController = Cast<ARunnerPlayerController>(Controller); RunnerController!= nullptr)
	{
		CurrentController = RunnerController;
	}
}

void AGameElementBase::ApplyPoint()
{
}

// Called every frame
void AGameElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	Location+= FVector(-Speed*DeltaTime,0,0);
	SetActorLocation(Location);

	if(Location.X<-100)
	{
		ApplyPoint();
		Destroy();
	}

}

