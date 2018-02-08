// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include <Engine/World.h>


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		AITank = Cast<ATank>(GetPawn());
		// TODO Move towards the player
		PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (AITank&&PlayerTank)
		{
			// Aim towards the player
			AITank->AimAt(PlayerTank->GetActorLocation());

			AITank->Fire();
		}
	}
}

