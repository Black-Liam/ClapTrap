// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "StoppingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class CLAPTRAP_API AStoppingPlatform : public AMovingPlatform
{
	GENERATED_BODY()
	
protected:

    virtual void BeginPlay() override;
};
