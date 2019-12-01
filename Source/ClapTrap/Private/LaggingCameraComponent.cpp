// Fill out your copyright notice in the Description page of Project Settings.


#include "LaggingCameraComponent.h"

void ULaggingCameraComponent::CatchUp(FVector focus)
{
    focus *= FVector(0, 0, 1);
    this->SetWorldLocation(focus + FVector(0.f, 500.f, 400.f));
}