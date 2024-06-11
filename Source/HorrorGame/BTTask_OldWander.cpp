// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_OldWander.h"
#include "AIController.h"
#include <NavigationSystem.h>
#include "Navigation/PathFollowingComponent.h"

UBTTask_OldWander::UBTTask_OldWander()
{
	NodeName = TEXT("OldWander");
}

EBTNodeResult::Type UBTTask_OldWander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto pawn = OwnerComp.GetAIOwner()->GetPawn()) {
		if (AAIController* AIController = Cast<AAIController>(pawn->GetController())) {
			FVector actorLocation = pawn->GetActorLocation();
			auto navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
			FNavLocation targetLocation;
			navSystem->GetRandomPointInNavigableRadius(actorLocation, 10000, targetLocation);
			//EPathFollowingRequestResult moveResult = AIController->MoveToLocation(targetLocation, wanderRadius, nullptr);
			FAIMoveRequest moveReq(targetLocation);
			EPathFollowingRequestResult::Type moveResult = AIController->MoveTo(moveReq, nullptr);
			if (moveResult == 0) {
				UE_LOG(LogTemp, Display, TEXT("returnin g failed"));
				return EBTNodeResult::Failed;
			}
			else {
				UE_LOG(LogTemp, Display, TEXT("returning Success"));
				return EBTNodeResult::Succeeded;
			}

		}
	}
	UE_LOG(LogTemp, Display, TEXT("Didnt' even get in"));
	return EBTNodeResult::Failed;
}
