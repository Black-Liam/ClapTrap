// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingEnemy.generated.h"

UCLASS()
class CLAPTRAP_API AFlyingEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyingEnemy();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent* EnemyCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* EnemySpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* SightSpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing", meta = (AllowPrivateAccess = "true"))
        class UEyesightComponent* EyesightComponent;


    UPROPERTY(EditAnywhere, Category = "AI")
        class APatrolPoint* StartPoint;

    UPROPERTY(EditAnywhere, Category = "AI")
        APatrolPoint* EndPoint;

    UPROPERTY(EditAnywhere, Category = "AI")
        TArray<APatrolPoint*> PatrolPoints;

    UPROPERTY(EditInstanceOnly, Category = "AI")
        APatrolPoint* Target;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
        void OnPawnSeen(APawn* SeenPawn);

    //TODO Week 10b:
    UFUNCTION()
        void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

    UPROPERTY(EditAnywhere, Category = "Movement")
        float speed = 400.0f;

    int nextLocation = 0;

public:	

    UFUNCTION()
        void SetPatrol(APatrolPoint* s, APatrolPoint* e);
    UFUNCTION()
        void SetSpeed(float v);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
