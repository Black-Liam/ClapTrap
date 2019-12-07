// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningManager.generated.h"

UCLASS()
class CLAPTRAP_API ASpawningManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningManager();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
        TSubclassOf<class AFloatingPlatform> FPlatformTemplate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
        TSubclassOf<class AMovingPlatform> MPlatformTemplate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
        TSubclassOf<class AStoppingPlatform> SPlatformTemplate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
        TSubclassOf<class APatrolPoint> PatrolTemplate;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrays")
        TArray<APatrolPoint*> PatrolPoints;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrays")
        TArray<AFloatingPlatform*> Platforms;

    UPROPERTY(BlueprintReadOnly)
        int platformNumber = 0;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        int numberOfPlatforms = 40;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        int movingPlatformFrequency = 3;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        int stoppingPlatformFrequency = 5;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        int sleepingEnemyFrequency = 4;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        int checkpointFrequency = 10;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        int flyingEnemyFrequency = 6;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SpawnPlatform();
};
