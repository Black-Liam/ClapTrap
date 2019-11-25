// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloatingPlatform.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class CLAPTRAP_API AMovingPlatform : public AFloatingPlatform
{
	GENERATED_BODY()
	
public:
    AMovingPlatform();

    UPROPERTY(EditAnywhere, Category = "AI")
        class APatrolPoint* StartPoint;

    UPROPERTY(EditAnywhere, Category = "AI")
        APatrolPoint* EndPoint;

    UPROPERTY(EditAnywhere, Category = "AI")
        TArray<APatrolPoint*> PatrolPoints;

    UPROPERTY(EditInstanceOnly, Category = "AI")
        APatrolPoint* Target;

protected:

    virtual void BeginPlay() override;

    

    float speed = 400.0f;
    int nextLocation = 0;

public:

    virtual void Tick(float DeltaTime) override;
};
