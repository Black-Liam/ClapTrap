// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "ClappingPawn.h"
#include "FloatingPlatform.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CheckpointCollision = CreateDefaultSubobject<UBoxComponent>("Capsule Collision");
    SetRootComponent(CheckpointCollision);
    CheckpointCollision->SetCollisionProfileName("Query and Physics");
    CheckpointCollision->SetNotifyRigidBodyCollision(true);
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(CheckpointCollision);
    CheckpointCollision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::Checked);

    CheckpointDown = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Visual");
    CheckpointDown->SetupAttachment(CheckpointCollision);
    CheckpointDown->SetCollisionProfileName("NoCollision");
    CheckpointDown->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CheckpointDown->SetGenerateOverlapEvents(false);

    CheckpointUp = CreateDefaultSubobject<UPaperSpriteComponent>("Death Visual");
    CheckpointUp->SetupAttachment(CheckpointCollision);
    CheckpointUp->SetCollisionProfileName("NoCollision");
    CheckpointUp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CheckpointUp->SetGenerateOverlapEvents(false);
    CheckpointUp->SetVisibility(false);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACheckpoint::Checked(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            AClappingPawn* player = Cast<AClappingPawn>(OtherActor);
            if (player)
            {
                CheckpointDown->SetVisibility(false);
                CheckpointUp->SetVisibility(true);
                player->lastCheckpoint = this;

            }
        }
    }
}