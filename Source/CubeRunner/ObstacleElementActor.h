// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElementBase.h"
#include "ObstacleElementActor.generated.h"

/**
 * 
 */
UCLASS()
class CUBERUNNER_API AObstacleElementActor : public AGameElementBase
{
	GENERATED_BODY()
public:
	AObstacleElementActor();

protected:
	void ReactToComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	void ReactToComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void ApplyPoint() override;
public:
	virtual void Tick(float DeltaSeconds) override;

};
