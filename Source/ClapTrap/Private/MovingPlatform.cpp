// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "..\Public\MovingPlatform.h"
#include "..\Public\PatrolPoint.h"


AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    StartPoint = CreateDefaultSubobject<APatrolPoint>("Start");
    StartPoint->SetActorLocation(RootComponent->GetComponentLocation() + FVector(0.0f, 0.0f, 100.0f));
    
    
    EndPoint = CreateDefaultSubobject<APatrolPoint>("End");
    EndPoint->SetActorLocation(RootComponent->GetComponentLocation() + FVector(0.0f, 0.0f, -100.0f));

}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    PatrolPoints.Add(StartPoint);
    PatrolPoints.Add(EndPoint);

    Target = PatrolPoints[nextLocation];
}

void AMovingPlatform::SetPatrol(APatrolPoint* s, APatrolPoint* e)
{
    StartPoint = s;
    EndPoint = e;
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bWillStop && bHasStopped){}
    else
    {
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
    
}