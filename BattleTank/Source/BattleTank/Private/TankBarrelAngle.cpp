// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelAngle.h"
#include <Engine/World.h>

void UTankBarrelAngle::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elvevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

}



