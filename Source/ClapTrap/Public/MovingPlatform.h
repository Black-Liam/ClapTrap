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
        class AActor* StartPoint;

    UPROPERTY(EditAnywhere, Category = "AI")
        AActor* EndPoint;

    UPROPERTY(EditAnywhere, Category = "AI")
        TArray<AActor*> PatrolPoints;

    UPROPERTY(EditInstanceOnly, Category = "AI")
        AActor* Target;

    UPROPERTY(EditAnywhere, Category = "AI")
        bool bHasStopped = false;

protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "AI")
        bool bWillStop = false;

    float speed = 400.0f;
    int nextLocation = 0;

public:

    virtual void Tick(float DeltaTime) override;
};
