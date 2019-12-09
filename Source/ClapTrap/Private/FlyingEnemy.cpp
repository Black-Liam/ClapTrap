// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingEnemy.h"
#include "Components/BoxComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "EyesightComponent.h"
#include "..\Public\PatrolPoint.h"

// Sets default values
AFlyingEnemy::AFlyingEnemy()
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

    SightSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Death Visual");
    SightSpriteComponent->SetupAttachment(EnemyCollision);
    SightSpriteComponent->SetCollisionProfileName("NoCollision");
    SightSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SightSpriteComponent->SetGenerateOverlapEvents(false);

    EyesightComponent = CreateDefaultSubobject<UEyesightComponent>(TEXT("PawnSensingComp"));

    EyesightComponent->OnSeePawn.AddDynamic(this, &AFlyingEnemy::OnPawnSeen);
    EyesightComponent->OnHearNoise.AddDynamic(this, &AFlyingEnemy::OnNoiseHeard);

}

// Called when the game starts or when spawned
void AFlyingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlyingEnemy::OnPawnSeen(APawn* SeenPawn)
{

}

void AFlyingEnemy::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{

}

void AFlyingEnemy::SetPatrol(APatrolPoint* s, APatrolPoint* e)
{
    StartPoint = s;
    EndPoint = e;

    PatrolPoints.Add(StartPoint);
    PatrolPoints.Add(EndPoint);

    Target = PatrolPoints[nextLocation];
}

void AFlyingEnemy::SetSpeed(float v)
{
    speed = v;
}

