// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningManager.h"
#include "ConstructorHelpers.h"
#include "FloatingPlatform.h"
#include "MovingPlatform.h"
#include "StoppingPlatform.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "PatrolPoint.h"


// Sets default values
ASpawningManager::ASpawningManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawningManager::BeginPlay()
{
	Super::BeginPlay();

    int num = 40;
#pragma region Platforms
    for (int i = 0; i < numberOfPlatforms; i++)
    {
        if (FPlatformTemplate && MPlatformTemplate && SPlatformTemplate)
        {
            //DECLARE a variable called World of type const UWorld* and assign it to the return value of GetWorld()
            UWorld* World = GetWorld();
            //IF World is NOT EQUAL to nullptr
            if (World)
            {
                float XOffset = (FMath::FRand() * 1000.f) - 500.f;

                FActorSpawnParameters SpawnParams;

                SpawnParams.Owner = this;

                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                FTransform SpawnTransform = GetTransform();
                SpawnTransform.SetLocation(SpawnTransform.GetLocation() + FVector(XOffset, 0, 400 * platformNumber));

                bool success = false;
                if (platformNumber == 0)
                {
                    FTransform firstTransform = GetTransform();
                    AFloatingPlatform* SpawnedActor = World->SpawnActor<AFloatingPlatform>(FPlatformTemplate, firstTransform, SpawnParams);
                    if (SpawnedActor)
                    {
                        success = true;
                        Platforms.Add(SpawnedActor);
                    }
                }
                else if (platformNumber % movingPlatformFrequency == 0)
                {
                    AMovingPlatform* SpawnedActor = World->SpawnActor<AMovingPlatform>(MPlatformTemplate, SpawnTransform, SpawnParams);
                    if (SpawnedActor)
                    {
                        success = true;
                        Platforms.Add(SpawnedActor);
                    }
                }
                else if (platformNumber % stoppingPlatformFrequency == 0)
                {
                    AStoppingPlatform* SpawnedActor = World->SpawnActor<AStoppingPlatform>(SPlatformTemplate, SpawnTransform, SpawnParams);
                    if (SpawnedActor)
                    {
                        success = true;
                        Platforms.Add(SpawnedActor);
                    }
                }
                else
                {
                    AFloatingPlatform* SpawnedActor = World->SpawnActor<AFloatingPlatform>(FPlatformTemplate, SpawnTransform, SpawnParams);
                    if (SpawnedActor)
                    {
                        success = true;
                        Platforms.Add(SpawnedActor);
                    }
                }
                if (success == true)
                {
                    platformNumber++;
                    success = false;
                }
            }
        }
    }

    for (int i = 0; i < 2 * numberOfPlatforms; i++)
    {
        if (PatrolTemplate)
        {
            UWorld* World = GetWorld();
            if (World)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = this;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                float XOffset = (FMath::FRand() * 1000.f) - 500.f;
                FTransform PatrolTransform = Platforms[i/2]->GetTransform();
                if (i % 2 == 0)
                {
                    PatrolTransform.SetLocation(PatrolTransform.GetLocation() + FVector(200, 0, 0));
                }
                else
                {
                    PatrolTransform.SetLocation(PatrolTransform.GetLocation() - FVector(200, 0, 0) );
                }
                APatrolPoint* patrolPoint = World->SpawnActor<APatrolPoint>(PatrolTemplate, PatrolTransform, SpawnParams);

                if (patrolPoint)
                {
                    PatrolPoints.Add(patrolPoint);
                }
            }
        }
    }

    for (int i = 0; i < numberOfPlatforms; i++)
    {
        AMovingPlatform* mover = Cast<AMovingPlatform>(Platforms[i]);
        if (mover)
            mover->SetPatrol(PatrolPoints[i * 2], PatrolPoints[i * 2 + 1]);
    }
#pragma endregion Platforms


}

// Called every frame
void ASpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}