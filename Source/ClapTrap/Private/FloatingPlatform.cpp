// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"


// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    PlatformCollision = CreateDefaultSubobject<UBoxComponent>("Collision");
    PlatformSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Visual");

    SetRootComponent(PlatformCollision);
    PlatformSpriteComponent->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

