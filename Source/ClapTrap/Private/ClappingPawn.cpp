// Fill out your copyright notice in the Description page of Project Settings.


#include "ClappingPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "LaggingCameraComponent.h"
#include "MovingPlatform.h"


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

    PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Visual");
    PawnSpriteComponent->SetupAttachment(CollisionCap);
    PawnSpriteComponent->SetCollisionProfileName("NoCollision");
    PawnSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PawnSpriteComponent->SetGenerateOverlapEvents(false);

    Camera = CreateDefaultSubobject<ULaggingCameraComponent>("Camera");
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(3000.0f);

    LandingOverlap = CreateDefaultSubobject<UBoxComponent>("Landing Gear");
    LandingOverlap->SetupAttachment(CollisionCap);
    LandingOverlap->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    LandingOverlap->SetGenerateOverlapEvents(true);
    LandingOverlap->OnComponentBeginOverlap.AddDynamic(this, &AClappingPawn::Landed);
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

}

// Called to bind functionality to input
void AClappingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &AClappingPawn::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AClappingPawn::MoveUp);
    //PlayerInputComponent->BindAction("Clap", IE_Pressed, this, &AClappingPawn::Clap);
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




    }
}

