// Fill out your copyright notice in the Description page of Project Settings.


#include "SleepingEnemy.h"

// Sets default values
ASleepingEnemy::ASleepingEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASleepingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASleepingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASleepingEnemy::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
    //TODO Week 10b:
    //CALL DrawDebugSphere() passing in (GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f)
    //DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

    //TODO Week 10b:
    //DECLARE a variable called Direction of type FVEctor and Assign it to the result of Location -  GetActorLocation()
    FVector Direction = Location - GetActorLocation();
    //TODO Week 10b:
    //CALL Normalize() on Direction
    Direction.Normalize();

    //TODO Week 10b:
    //DECLARE a variable called NewLookAt of type FRotator and SET it to the return value of FRotationMatrix::MakeFromX(Direction).Rotator()
    FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
    //TODO Week 10b:
    //SET NewLookAt.Pitch to 0.0f
    NewLookAt.Pitch = 0.0f;
    //TODO Week 10b:
    //SET NewLookAt.Roll to 0.0f
    NewLookAt.Roll = 0.0f;

    //TODO Week 10b:
    //CALL SetActorRotation() passing in NewLookAt
    SetActorRotation(NewLookAt);

}

