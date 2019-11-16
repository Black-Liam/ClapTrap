// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "..\Public\MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    StartPoint = CreateDefaultSubobject<AActor>("Start");
    StartPoint->SetActorLocation(RootComponent->GetComponentLocation() + FVector(0.0f, 100.0f, 0.0f));


    EndPoint = CreateDefaultSubobject<AActor>("End");
    EndPoint->SetActorLocation(RootComponent->GetComponentLocation() + FVector(0.0f, -100.0f, 0.0f));

}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    PatrolPoints.Add(StartPoint);
    PatrolPoints.Add(EndPoint);

    Target = PatrolPoints[nextLocation];
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector thisLocation = GetActorLocation();
    FVector thatLocation = Target->GetActorLocation();

    FVector targetLocation = FMath::VInterpConstantTo(thisLocation, thatLocation, DeltaTime, speed);

    SetActorLocation(targetLocation);

    if (thisLocation.Distance(thisLocation, thatLocation) < 10.0f)
    {
        if (Target == PatrolPoints.Last())
            nextLocation = 0;
        else
            nextLocation++;

        Target = PatrolPoints[nextLocation];
    }
}