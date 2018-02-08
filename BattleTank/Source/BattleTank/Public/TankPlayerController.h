// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D& ScreenLocation, FVector& WorldDirection) const;

	bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation=0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation=0.33333;

	float LineTraceRange = 1000000;
};

