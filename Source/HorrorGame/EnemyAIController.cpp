// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"


//void AEnemyAIController::BeginPlay()
//{
//	Super::BeginPlay();
//}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(AIBehavior);
}
