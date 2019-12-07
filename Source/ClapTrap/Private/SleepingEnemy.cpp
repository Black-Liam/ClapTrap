// Fill out your copyright notice in the Description page of Project Settings.


#include "SleepingEnemy.h"
#include "Components/BoxComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ASleepingEnemy::ASleepingEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    EnemyCollision = CreateDefaultSubobject<UBoxComponent>("Capsule Collision");
    SetRootComponent(EnemyCollision);
    EnemyCollision->SetCollisionProfileName("BlockAll");
    EnemyCollision->SetNotifyRigidBodyCollision(true);
    EnemyCollision->SetSimulatePhysics(true);
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(EnemyCollision);

    EnemySpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite Visual");
    EnemySpriteComponent->SetupAttachment(EnemyCollision);
    EnemySpriteComponent->SetCollisionProfileName("NoCollision");
    EnemySpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    EnemySpriteComponent->SetGenerateOverlapEvents(false);

}

// Called when the game starts or when spawned
void ASleepingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASleepingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASleepingEnemy::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
    if (Volume >= 1.0)
    {

    }


}

