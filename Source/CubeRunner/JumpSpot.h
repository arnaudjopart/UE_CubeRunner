// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElementBase.h"
#include "JumpSpot.generated.h"

/**
 * 
 */
UCLASS()
class CUBERUNNER_API AJumpSpot : public AGameElementBase
{
	GENERATED_BODY()
public:
	AJumpSpot();
	protected:
	virtual void ReactToComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditAnywhere, Category="Behaviour")
	float FloorLevel = 300;
	UPROPERTY(EditAnywhere, Category="Behaviour")
	float MaxJumpHeight=500;
};
