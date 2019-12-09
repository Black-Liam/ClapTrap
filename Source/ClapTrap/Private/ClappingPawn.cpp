// Fill out your copyright notice in the Description page of Project Settings.


#include "ClappingPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "LaggingCameraComponent.h"
#include "MovingPlatform.h"
#include "Components/AudioComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Checkpoint.h"


// Sets default values
AClappingPawn::AClappingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionCap = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collision");
    SetRootComponent(CollisionCap);
    CollisionCap->SetCollisionProfileName("BlockAll");
    CollisionCap->SetNotifyRigidBodyCollision(true);
    CollisionCap->SetSimulatePhysics(true);
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(CollisionCap);
    Tags.Add("Player");

    PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Visual");
    PawnSpriteComponent->SetupAttachment(CollisionCap);
    PawnSpriteComponent->SetCollisionProfileName("NoCollision");
    PawnSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PawnSpriteComponent->SetGenerateOverlapEvents(false);

    ClapSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Clap Visual");
    ClapSprite->SetupAttachment(CollisionCap);
    ClapSprite->SetCollisionProfileName("NoCollision");
    ClapSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ClapSprite->SetGenerateOverlapEvents(false);
    ClapSprite->SetVisibility(false);

    Camera = CreateDefaultSubobject<ULaggingCameraComponent>("Camera");
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(2500.0f);

    LandingOverlap = CreateDefaultSubobject<UBoxComponent>("Landing Gear");
    LandingOverlap->SetupAttachment(CollisionCap);
    LandingOverlap->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    LandingOverlap->SetGenerateOverlapEvents(true);
    LandingOverlap->OnComponentBeginOverlap.AddDynamic(this, &AClappingPawn::Landed);

    NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));
}

// Called when the game starts or when spawned
void AClappingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClappingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    clapTimer += DeltaTime;
    if (clapTimer <= 0.5 && bClapped)
    {
        MakeNoise(1.0f, this, GetActorLocation(), 150.0f);
    }
    else if (clapTimer > 0.5 && clapTimer < 1.0)
    {
        //ClapSprite->SetSpriteColor(FLinearColor(1.0, 1.0, 1.0, 0.0));
        ClapSprite->SetVisibility(false);
    }
    else if (clapTimer >= 3 && bClapped)
    {
        bClapped = false;
    }
}

// Called to bind functionality to input
void AClappingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &AClappingPawn::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AClappingPawn::MoveUp);
    PlayerInputComponent->BindAction("ClapAction", IE_Pressed, this, &AClappingPawn::Clap);
}

void AClappingPawn::MoveRight(float value)
{
    if (value != 0)
    {
        FVector currentVel = CollisionCap->BodyInstance.GetUnrealWorldVelocity();
        if (FMath::Abs(currentVel.X) < MaxVelX)
        {
            CollisionCap->BodyInstance.AddForce(FVector(1.0f, 0.0f, 0.0f) * value * Xspeed);
        }
        else
        {
            FVector newVel = FVector(MaxVelX * value, 0.0f, currentVel.Z);
            CollisionCap->BodyInstance.SetLinearVelocity(newVel, false);
        }
    }
}

void AClappingPawn::Clap()
{
    if (!bClapped)
    {
        MakeNoise(1.1f, this, GetActorLocation(), 150.0f);
        //ClapSprite->SetSpriteColor(FLinearColor(1.0, 1.0, 1.0, 1.0));
        ClapSprite->SetVisibility(true);
        clapTimer = 0.0;
        bClapped = true;
    }
}

void AClappingPawn::MoveUp()
{
    if (bOnFloor)
    {
        bOnFloor = false;
        CollisionCap->BodyInstance.AddForce(FVector(0.0f, 0.0f, 1.0f) * Yspeed * 100);
    }
}

void AClappingPawn::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor)
    {
        if (OtherActor->ActorHasTag("Enemy"))
        {
            returnToCheckpoint();
        }
    }
}

void AClappingPawn::Landed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        if (OtherActor->ActorHasTag("Platform"))
        {
            bOnFloor = true;
            AMovingPlatform* landing = Cast<AMovingPlatform>(OtherActor);
            if (landing)
            {
                landing->bHasStopped = true;
            }
                
            Camera->CatchUp(this->GetActorLocation());
            CollisionCap->SetPhysicsLinearVelocity(FVector(0,0,0));
        }
        if (OtherActor->ActorHasTag("Enemy"))
        {
            returnToCheckpoint();
        }



    }
}

void AClappingPawn::returnToCheckpoint()
{
    if (lastCheckpoint)
    {
        CollisionCap->BodyInstance.ClearForces();
        this->SetActorLocation(lastCheckpoint->GetActorLocation());
        Camera->GoBack(GetActorLocation());
    }
    else
    {
        CollisionCap->BodyInstance.ClearForces();
        this->SetActorLocation(FVector(0,0,50));
        Camera->GoBack(GetActorLocation());
    }
}

