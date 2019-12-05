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

    for (int i = 0; i < 5; i++)
    {
        SpawnPlatform();
    }
	
}

// Called every frame
void ASpawningManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawningManager::SpawnPlatform()
{
    if (FPlatformTemplate && MPlatformTemplate && SPlatformTemplate && PatrolTemplate)
    {
        //DECLARE a variable called World of type const UWorld* and assign it to the return value of GetWorld()
        UWorld* World = GetWorld();
        //IF World is NOT EQUAL to nullptr
        if (World)
        {
            float XOffset = (FMath::FRand() * 1000.f) - 500.f;

            //DECLARE a variable called SpawnParams of type FActorSpawnParameters
            FActorSpawnParameters SpawnParams;
            //SET SpawnParams Owner to this
            SpawnParams.Owner = this;
            //SET SpawnParams SpawnCollisionHandlingOverride property to ESpawnActorCollisionHandlingMethod::AlwaysSpawn
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            //DECLARE a variable called SpawnTransform of type FTransform and assign it to the return value of SpawnPointComponent->GetComponentTransform()
            FTransform SpawnTransform = GetTransform();
            SpawnTransform.SetLocation(SpawnTransform.GetLocation() + FVector(XOffset,0,300*platformNumber));

            FTransform PatrolTransform1 = GetTransform();
            PatrolTransform1.SetLocation(PatrolTransform1.GetLocation() + FVector(100, 0, 0) + FVector(XOffset, 0, 300 * platformNumber));

            FTransform PatrolTransform2 = GetTransform();
            PatrolTransform2.SetLocation(PatrolTransform2.GetLocation() - FVector(100, 0, 0) + FVector(XOffset, 0, 300 * platformNumber));

            bool success = 0;

            //DECLARE a variable called SpawnedActor of type AFallingActor* and assign it to the return value of World->SpawnActor<type>(args..), 
            //passing in AFallingActor as the type argument (inside <>) and in function arguments pass --> FallingActorTemplate, SpawnTransform, SpawnParams
            //SpawnActor() is a very important Function, it Instantiates the TSubclassOf template class that we set in the editor. 
            if (platformNumber == 0)
            {
                AFloatingPlatform* SpawnedActor = World->SpawnActor<AFloatingPlatform>(FPlatformTemplate, SpawnTransform, SpawnParams);
                if (SpawnedActor)
                {
                    success = 1;
                }
            }
            else if (platformNumber % 7 == 0)
            {
                AMovingPlatform* SpawnedActor = World->SpawnActor<AMovingPlatform>(MPlatformTemplate, SpawnTransform, SpawnParams);
                APatrolPoint* patrolPoint1 = World->SpawnActor<APatrolPoint>(PatrolTemplate, PatrolTransform1, SpawnParams);
                APatrolPoint* patrolPoint2 = World->SpawnActor<APatrolPoint>(PatrolTemplate, PatrolTransform2, SpawnParams);
                SpawnedActor->SetPatrol(patrolPoint1, patrolPoint2);
                if (SpawnedActor && patrolPoint1 && patrolPoint2)
                {
                    success = 1;
                }
            }
            else if (platformNumber % 3 == 0)
            {
                AStoppingPlatform* SpawnedActor = World->SpawnActor<AStoppingPlatform>(SPlatformTemplate, SpawnTransform, SpawnParams);
                APatrolPoint* patrolPoint1 = World->SpawnActor<APatrolPoint>(PatrolTemplate, PatrolTransform1, SpawnParams);
                APatrolPoint* patrolPoint2 = World->SpawnActor<APatrolPoint>(PatrolTemplate, PatrolTransform2, SpawnParams);
                SpawnedActor->SetPatrol(patrolPoint1, patrolPoint2);
                if (SpawnedActor && patrolPoint1 && patrolPoint2)
                {
                    success = 1;
                }
            }
            else
            {
                AFloatingPlatform* SpawnedActor = World->SpawnActor<AFloatingPlatform>(FPlatformTemplate, SpawnTransform, SpawnParams);
                if (SpawnedActor)
                {
                    success = 1;
                }
            }
            if (success)
            {
                platformNumber++;
            }
        }
    }
}

