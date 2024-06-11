// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT("Update Player Location");
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	if (APawn* targetPlayer = Cast<APawn>(blackBoardComp->GetValueAsObject(TEXT("targetPlayer")))) {
		blackBoardComp->SetValueAsVector(TEXT("targetPlayerLocation"), targetPlayer->GetActorLocation());
	}
}
