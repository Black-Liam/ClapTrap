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

    UPROPERTY(BlueprintReadOnly)
        int platformNumber = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SpawnPlatform();
};
