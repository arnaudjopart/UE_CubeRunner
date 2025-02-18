// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpSpot.h"

AJumpSpot::AJumpSpot()
{
	
}

void AJumpSpot::ReactToComponentOverlap(UPrimitiveComponent* OverlappedComponent,
										AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp,
                                        int32 OtherBodyIndex,
                                        bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	Super::ReactToComponentOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (APlayerPawn* MyPawn = Cast<APlayerPawn>(OtherActor);MyPawn!=nullptr)
	{
		MyPawn->Jump(MaxJumpHeight,FloorLevel);
	}
}
