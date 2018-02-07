// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include "TankBarrel1.h"
#include "TankBarrelAngle.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelRefference(UTankBarrel1 * BarrelToSet, UTankBarrelAngle * AngleToSet)
{
	if (!BarrelToSet) {	return;	}
	Barrel1 = BarrelToSet;
	BarrelAngle = AngleToSet;
}

void UTankAimingComponent::SetTurretRefference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
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
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!BarrelAngle) {	return;	}
	// Work-out difference between current barrel rotation, and AimDireciton
	auto BarrelRotator = BarrelAngle->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	BarrelAngle->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!Turret) { return;	}
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
	Turret->Rotate(DeltaRotator.Yaw);
}