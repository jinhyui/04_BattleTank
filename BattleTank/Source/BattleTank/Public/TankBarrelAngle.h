// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TankBarrelAngle.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrelAngle : public USceneComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreePerSecond = 10;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = -20; 

	
	
	
	
};
