// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNewWanderLocation.h"
#include <NavigationSystem.h>
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


UBTTask_FindNewWanderLocation::UBTTask_FindNewWanderLocation()
{
	NodeName = TEXT("Find New Wander Location");
}

EBTNodeResult::Type UBTTask_FindNewWanderLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto pawn = OwnerComp.GetAIOwner()->GetPawn()) {
		if (AAIController* AIController = Cast<AAIController>(pawn->GetController())) {
			FVector actorLocation = pawn->GetActorLocation();
			auto navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
			FNavLocation targetNavLocation;
			navSystem->GetRandomPointInNavigableRadius(actorLocation, searchRadius, targetNavLocation);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetNavLocation.Location);
		}
	}
	return EBTNodeResult::Succeeded;
}
