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
    EnemyCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    EnemyCollision->SetNotifyRigidBodyCollision(true);
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(EnemyCollision);
    Tags.Add("Enemy");

    EnemySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Visual");
    EnemySpriteComponent->SetupAttachment(EnemyCollision);
    EnemySpriteComponent->SetCollisionProfileName("NoCollision");
    EnemySpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    EnemySpriteComponent->SetGenerateOverlapEvents(false);

    EyesightComponent = CreateDefaultSubobject<UEyesightComponent>(TEXT("PawnSensingComp"));

    EyesightComponent->OnSeePawn.AddDynamic(this, &AFlyingEnemy::OnPawnSeen);
    EyesightComponent->OnHearNoise.AddDynamic(this, &AFlyingEnemy::OnNoiseHeard);

    StartPoint = CreateDefaultSubobject<APatrolPoint>("Start");
    EndPoint = CreateDefaultSubobject<APatrolPoint>("End");

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

    FVector thisLocation = GetActorLocation();
    FVector thatLocation = Target->GetActorLocation();

    FVector targetLocation = FMath::VInterpConstantTo(thisLocation, thatLocation, DeltaTime, speed);

    SetActorLocation(targetLocation);

    if (thisLocation.Distance(thisLocation, thatLocation) < 10.0f)
    {
        if (Target == PatrolPoints.Last())
            nextLocation = 0;
        else
            nextLocation++;

        Target = PatrolPoints[nextLocation];
    }


}

void AFlyingEnemy::OnPawnSeen(APawn* SeenPawn)
{

}

void AFlyingEnemy::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
    if (Volume >= 1.0)
    {
        Destroy();
    }
    else
    {
        
    }
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

