// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include "TankBarrel1.h"
#include "TankBarrelAngle.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelRefference(UTankBarrel1 * BarrelToSet, UTankBarrelAngle * AngleToSet)
{
	Barrel1 = BarrelToSet;
	BarrelAngle = AngleToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!BarrelAngle||!Barrel1) {
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel1->GetSocketLocation(FName("Projectile"));
	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation, and AimDireciton
	auto BarrelRotator = BarrelAngle->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *AimAsRotator.ToString());

	BarrelAngle->Elevate(5); // TODO remove magis number
}