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

protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "Others"))
        TArray<AActor*> PatrolPoints;

    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "Target"))
        AActor* StartPoint;

    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "Target"))
        AActor* EndPoint;

    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "Target"))
        AActor* Target;

    float speed = 400.0f;
    int nextLocation = 0;

public:

    virtual void Tick(float DeltaTime) override;
};
