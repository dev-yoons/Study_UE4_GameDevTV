// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr)
		return EBTNodeResult::Failed;
	AShooterCharacter* MyShooter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyShooter == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	MyShooter->Shoot();
	return EBTNodeResult::Succeeded;
}
