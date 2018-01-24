// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrelAngle;
class UTankBarrel1;
class UTankTurret;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelRefference(UTankBarrel1 * BarrelToSet, UTankBarrelAngle * AngleToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);


private:
	UTankBarrelAngle * BarrelAngle = nullptr;
	UTankBarrel1 * Barrel1 = nullptr;
	UTankTurret * Turret = nullptr;
};