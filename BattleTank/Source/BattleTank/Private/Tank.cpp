
// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include <Engine/World.h>
#include "TankBarrel1.h"
#include "Projectile.h"

// Set defalt value
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelRefference(UTankBarrel1 * BarrelToSet, UTankBarrelAngle * AngleToSet)
{
	TankAimingComponent->SetBarrelRefference(BarrelToSet, AngleToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretRefference(UTankTurret * TankTurret)
{
	TankAimingComponent->SetTurretRefference(TankTurret);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel) {	return;	}

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBluprinter,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);
}