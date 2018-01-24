// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include <Engine/World.h>

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, 0, RawNewRotation));

}


