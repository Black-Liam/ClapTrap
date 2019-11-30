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

    UPROPERTY(EditAnywhere, Category = "Collision")
        class UCapsuleComponent* CollisionCap;

    UPROPERTY(EditAnywhere, Category = "Camera")
        class ULaggingCameraComponent* Camera;

    UFUNCTION()
        void MoveRight(float value);

        void Clap();

    void MoveUp();

    UFUNCTION()
        virtual	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


    UPROPERTY(EditAnywhere, Category = "Movement")
    bool bOnFloor = false;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxVelX = 50000.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Xspeed = 5000.0f;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Yspeed = 10000.0f;

    //class AMyPlayerState* myPlayerState;
};
