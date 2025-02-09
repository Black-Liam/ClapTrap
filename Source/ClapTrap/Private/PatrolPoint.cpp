// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPoint.h"
#include "PaperSpriteComponent.h"

// Sets default values
APatrolPoint::APatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Visual");
    SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SpriteComponent->SetCollisionProfileName("OverlapAll");
    SetRootComponent(SpriteComponent);
}

// Called when the game starts or when spawned
void APatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

