// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class CLAPTRAP_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Collision")
        class UBoxComponent* CheckpointCollision;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* CheckpointDown;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* CheckpointUp;

    UPROPERTY(EditAnywhere, Category = "Location")
        class AFloatingPlatform* myPlat;

    UFUNCTION()
        void Checked(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
