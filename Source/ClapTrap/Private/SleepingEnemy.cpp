// Fill out your copyright notice in the Description page of Project Settings.


#include "SleepingEnemy.h"

// Sets default values
ASleepingEnemy::ASleepingEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

