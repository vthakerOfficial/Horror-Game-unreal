// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"


UBTTask_SetPlayerLocation::UBTTask_SetPlayerLocation()
{
	NodeName = TEXT("Set Player Location");
}

EBTNodeResult::Type UBTTask_SetPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	if (APawn* targetPlayer = Cast<APawn>(blackBoardComp->GetValueAsObject(TEXT("targetPlayer")))) {
		blackBoardComp->SetValueAsVector(TEXT("targetPlayerLocation"), targetPlayer->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}
