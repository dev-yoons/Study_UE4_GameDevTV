// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerTank || DistanceToPlayer() > FireRange)
	{
		return;
	}
	Super::RotateTurretFunction(PlayerTank->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerTank || !PlayerTank->GetIsPlayerAlive())
		return;
	if (DistanceToPlayer() <= FireRange)
	{
		Super::Fire();
	}
}

float APawnTurret::DistanceToPlayer()
{
	if (!PlayerTank)
		return 0.0f;

	return FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
	
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
