// Fill out your copyright notice in the Description page of Project Settings.


#include "LaggingCameraComponent.h"

void ULaggingCameraComponent::CatchUp(FVector focus)
{
    if (focus.Z > GetRelativeTransform().GetLocation().Z)
    {
        focus *= FVector(0, 0, 1);
        this->SetRelativeLocation(focus + FVector(0.f, 500.f, 300.f));
    }
}