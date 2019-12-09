// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningManager.h"
#include "ConstructorHelpers.h"
#include "FloatingPlatform.h"
#include "MovingPlatform.h"
#include "StoppingPlatform.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "PatrolPoint.h"
#include "SleepingEnemy.h"
#include "FlyingEnemy.h"


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
        {
            mover->SetPatrol(PatrolPoints[i * 2], PatrolPoints[i * 2 + 1]);
            mover->SetSpeed((FMath::FRand() * 50.f) + 300.f + (i * 1.f));
        }
           
    }
#pragma endregion Platforms

#pragma region Enemies

    for (int i = 0; i < numberOfPlatforms; i++)
    {
        if (i % sleepingEnemyFrequency == 0)
        {
            if (SleepingTemplate)
            {
                UWorld* World = GetWorld();
                if (World)
                {
                    FActorSpawnParameters SpawnParams;
                    SpawnParams.Owner = this;
                    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                    FTransform EnemyTransform;
                    EnemyTransform.SetLocation(FVector(1000,1000,1000));
                    ASleepingEnemy* enemy = World->SpawnActor<ASleepingEnemy>(SleepingTemplate, EnemyTransform, SpawnParams);

                    if (enemy)
                    {
                        SleepingEnemies.Add(enemy);
                    }
                }
            }
        }
    }

    //Spawn flying enemies
    for (int i = 1; i < numberOfPlatforms; i++)
    {
        if (i % flyingEnemyFrequency == 0)
        {
            if (FlyingTemplate)
            {
                UWorld* World = GetWorld();
                if (World)
                {
                    FActorSpawnParameters SpawnParams;
                    SpawnParams.Owner = this;
                    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                    FTransform EnemyTransform;
                    EnemyTransform.SetLocation(EnemyTransform.GetLocation() + FVector(-1000, -1000, -1000));
                    AFlyingEnemy* enemy = World->SpawnActor<AFlyingEnemy>(FlyingTemplate, EnemyTransform, SpawnParams);
    
                    if (enemy)
                    {
                        FlyingEnemies.Add(enemy);
                        flyingNumber++;
                    }
                }
            }
        }
    }

    //spawn flying enemy patrol
    for (int i = 0; i < 2 * flyingNumber; i++)
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
                FTransform PatrolTransform = Platforms[(i/2) * flyingEnemyFrequency]->GetTransform();
                if (i % 2 == 0)
                {
                    PatrolTransform.SetLocation(PatrolTransform.GetLocation() + FVector(400, 0, 300));
                }
                else
                {
                    PatrolTransform.SetLocation(PatrolTransform.GetLocation() + FVector(-400, 0, 300));
                }
                APatrolPoint* patrolPoint = World->SpawnActor<APatrolPoint>(PatrolTemplate, PatrolTransform, SpawnParams);

                if (patrolPoint)
                {
                    FlyingPatrolPoints.Add(patrolPoint);
                }
            }
        }
    }

    //Attaching Sleeping to platforms
    for (int i = 1; i < numberOfPlatforms; i++)
    {
        if (i % sleepingEnemyFrequency == 0)
        {
            if (Platforms[i])
                SleepingEnemies[i / sleepingEnemyFrequency]->myPlat = Platforms[i];
        }
    }

    //Attach flying enemies to their patrol points
    for (int i = 0; i < flyingNumber; i++)
    {
        FlyingEnemies[i]->SetPatrol(FlyingPatrolPoints[i * 2], FlyingPatrolPoints[i * 2 + 1]);
        FlyingEnemies[i]->SetSpeed((FMath::FRand() * 50.f) + 300.f + (i * 1.f));
    }

#pragma endregion Enemies


#pragma region Checkpoint





#pragma endregion Checkpoint


}

// Called every frame
void ASpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}