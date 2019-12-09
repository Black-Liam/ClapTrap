// Fill out your copyright notice in the Description page of Project Settings.


#include "SleepingEnemy.h"
#include "Components/BoxComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "FloatingPlatform.h"

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
    Tags.Add("Enemy");

    EnemySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Visual");
    EnemySpriteComponent->SetupAttachment(EnemyCollision);
    EnemySpriteComponent->SetCollisionProfileName("NoCollision");
    EnemySpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    EnemySpriteComponent->SetGenerateOverlapEvents(false);

    DeathSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Death Visual");
    DeathSpriteComponent->SetupAttachment(EnemyCollision);
    DeathSpriteComponent->SetCollisionProfileName("NoCollision");
    DeathSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DeathSpriteComponent->SetGenerateOverlapEvents(false);

    ListeningComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("ListeningComp"));
    ListeningComponent->OnHearNoise.AddDynamic(this, &ASleepingEnemy::OnNoiseHeard);


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
    SetActorLocation(myPlat->GetActorLocation() + FVector(0.0, 0.0, 40.0));

    timer += DeltaTime;

    if (bHasDied && timer >= 1.0)
        Destroy();

}

void ASleepingEnemy::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
    if (Volume >= 1.0)
    {
        EnemySpriteComponent->SetSpriteColor(FLinearColor(1.0, 1.0, 1.0, 0.0));
        DeathSpriteComponent->SetSpriteColor(FLinearColor(1.0, 1.0, 1.0, 1.0));
        timer = 0.0f;
        bHasDied = true;
    }
}

