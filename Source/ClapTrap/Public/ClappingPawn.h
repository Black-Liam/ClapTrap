// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ClappingPawn.generated.h"

UCLASS()
class CLAPTRAP_API AClappingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AClappingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* PawnSpriteComponent;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* ClapSprite;

    UPROPERTY(EditAnywhere, Category = "Collision")
        class UCapsuleComponent* CollisionCap;

    UPROPERTY(EditAnywhere, Category = "Camera")
        class ULaggingCameraComponent* Camera;

    UPROPERTY(EditAnywhere, Category = "Collision")
        class UBoxComponent* LandingOverlap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
        class UPawnNoiseEmitterComponent* NoiseEmitterComponent;

    UFUNCTION()
        void MoveRight(float value);

        void Clap();
        float clapTimer = 0;
        bool bClapped = false;

    void MoveUp();

    UFUNCTION()
        virtual	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
        void Landed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere, Category = "Movement")
    bool bOnFloor = false;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxVelX = 50000.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Xspeed = 5000.0f;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Yspeed = 10000.0f;

    UPROPERTY(EditAnywhere, Category = "Level")
        class ACheckpoint* lastCheckpoint;

    UFUNCTION()
        void returnToCheckpoint();

};
