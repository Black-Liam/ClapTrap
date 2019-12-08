// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SleepingEnemy.generated.h"

class APawn;

UCLASS()
class CLAPTRAP_API ASleepingEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASleepingEnemy();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent* EnemyCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* EnemySpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* DeathSpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing", meta = (AllowPrivateAccess = "true"))
        class UPawnSensingComponent* ListeningComponent;

    UPROPERTY(EditInstanceOnly, Category = "Location")
        class AFloatingPlatform* myPlat;

    float timer = 0;
    bool bHasDied;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
        void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
