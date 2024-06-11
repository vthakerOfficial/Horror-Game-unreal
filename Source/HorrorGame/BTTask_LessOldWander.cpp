// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LessOldWander.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"


UBTTask_LessOldWander::UBTTask_LessOldWander()
{
	NodeName = TEXT("Less Old Wander");
}

void UBTTask_LessOldWander::resetWanderLogic()
{
	targetNavLocation.NodeRef = INVALID_NAVNODEREF;
	targetNavLocation.Location = FVector::ZeroVector;
}

EBTNodeResult::Type UBTTask_LessOldWander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (targetNavLocation.Location == FVector::ZeroVector) {
		findNewTargetLocation(OwnerComp);
	}
	EBTNodeResult::Type moveResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (moveResult == EPathFollowingRequestResult::AlreadyAtGoal) {
		//targetNavLocation.Location = FVector::ZeroVector;
		return EBTNodeResult::Succeeded;
	}
	else if (moveResult == EPathFollowingRequestResult::RequestSuccessful) {
		return EBTNodeResult::InProgress;
	}
	else {
		//targetNavLocation.Location = FVector::ZeroVector;
		return EBTNodeResult::Failed;
	}

}
/*
	// check if still going to some locatino
	//

	if (auto pawn = OwnerComp.GetAIOwner()->GetPawn()) {
		if (AAIController* AIController = Cast<AAIController>(pawn->GetController())) {
			FVector actorLocation = pawn->GetActorLocation();

			// checking if at previously set target location

			// moving if targetLocation is set
			if (targetNavLocation.HasNodeRef()) {
				EBTNodeResult::Type result = myMove(AIController);
				if (result == EBTNodeResult::Succeeded) {
					// finding new location to wander to
					findNewTargetLocation(actorLocation);
				}
				return result;
			}
			else { // finding a new point in world to wander towards
				findNewTargetLocation(actorLocation);
			}




			//UE_LOG(LogTemp, Display, TEXT("targetLocation = %s"), targetLocation.ToString());
			//OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), newTargetLocation);
			//return Super::PerformMoveTask(OwnerComp, NodeMemory);
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Didnt' even get in"));
	return EBTNodeResult::Failed;
}
*/
EBTNodeResult::Type UBTTask_LessOldWander::myMove(AAIController* AIController)
{

	FAIMoveRequest moveReq(targetNavLocation);
	EPathFollowingRequestResult::Type moveResult = AIController->MoveTo(moveReq, nullptr);
	if (moveResult == EPathFollowingRequestResult::AlreadyAtGoal) {
		return EBTNodeResult::Succeeded;
	}
	else if (moveResult == EPathFollowingRequestResult::RequestSuccessful) {
		return EBTNodeResult::InProgress;
	}
	else {
		return EBTNodeResult::Failed;
	}
}

void UBTTask_LessOldWander::findNewTargetLocation(UBehaviorTreeComponent& OwnerComp)
{
	if (auto pawn = OwnerComp.GetAIOwner()->GetPawn()) {
		if (AAIController* AIController = Cast<AAIController>(pawn->GetController())) {
			FVector actorLocation = pawn->GetActorLocation();
			auto navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
			FNavLocation newTargetNavLocation;
			navSystem->GetRandomPointInNavigableRadius(actorLocation, 10000, newTargetNavLocation);
			targetNavLocation = newTargetNavLocation;
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetNavLocation.Location);
		}
	}
}
