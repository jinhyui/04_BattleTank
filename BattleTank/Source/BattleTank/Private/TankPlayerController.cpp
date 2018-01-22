// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <Engine/World.h>

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing the tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing : %s"), *(ControlledTank->GetName()));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX *CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection)
{
	FVector WorldLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection));
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation)
{
	FHitResult Hit;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation(); //GetWorld()->GetFirstPlayerController()->GetPawn()->GetTargetLocation();
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		StartLocation + LookDirection * LineTraceRange,
		ECC_Visibility)
		)
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
		
		



