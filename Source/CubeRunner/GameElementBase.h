// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerPlayerController.h"
#include "GameFramework/Actor.h"
#include "GameElementBase.generated.h"

UCLASS()
class CUBERUNNER_API AGameElementBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameElementBase();
	
protected:
	UFUNCTION()
	virtual void ReactToComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void ReactToComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	float Speed=500;
	ARunnerPlayerController* CurrentController;
	virtual void ApplyPoint();

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetSpeed(float SpawnSpeed);

};
