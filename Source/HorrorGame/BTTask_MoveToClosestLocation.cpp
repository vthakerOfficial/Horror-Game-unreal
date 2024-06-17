// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToClosestLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/NavigationSystemBase.h"
#include <NavigationSystem.h>


UBTTask_MoveToClosestLocation::UBTTask_MoveToClosestLocation()
{
	NodeName = TEXT("Move To Closest Navigable Location");
}

EBTNodeResult::Type UBTTask_MoveToClosestLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	return result;
	/*
	if (result != EBTNodeResult::Failed) {
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Invalid position getting as close as possible")));
	}

	// at an inaccessilbe point so we will get as close as possible to pawn
	if (APawn* controlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn())) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("A")));
		}
		FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		FVector newTargetLocation = getClosestNavigablePoint(targetLocation);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), newTargetLocation);
		result = Super::ExecuteTask(OwnerComp, NodeMemory);
		if (result != EBTNodeResult::Failed) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("B")));
			}
			// player 
			if (APawn* targetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("targetPlayer")))) {
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("c")));
				}
				AController* targetPawnController = targetPawn->GetController();
				FRotator targetPawnRotation = targetPawnController->GetControlRotation();

				// AI (this)
				FVector AILocation = controlledPawn->GetActorLocation();
				
				// both
				FVector targetPawnLocation = targetPawn->GetActorLocation();
				FVector relativeVector = FVector(AILocation.X - targetPawnLocation.X, AILocation.Y - targetPawnLocation.Y, AILocation.Z - targetPawnLocation.Z);
				
				// setting player rotation
				targetPawnRotation.Yaw = relativeVector.Rotation().Yaw;
				targetPawnController->SetControlRotation(targetPawnRotation);

				// setting ai rotation
				FRotator AIRotation = controlledPawn->GetController()->GetControlRotation();
				AIRotation.Yaw = relativeVector.Rotation().Yaw + 180.0f;
				controlledPawn->GetController()->SetControlRotation(AIRotation);

				UE_LOG(LogTemp, Display, TEXT("new yaw is: %f"), relativeVector.Rotation().Yaw);
			}
		}
		
		//UE_LOG(LogTemp, Display, TEXT("Inaccessible target Location, getting as close as possible to targetPawn"));
		//UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

		//float val = 999999.0f;

		//FVector queryExtent = FVector(val, val, val);
		//FNavLocation navLoc;
		//bool bSuccess = navSystem->ProjectPointToNavigation(targetLocation, navLoc, queryExtent);
		//UE_LOG(LogTemp, Display, TEXT("bSuccess: %d"), bSuccess);
		//if (!bSuccess) return EBTNodeResult::Failed;
		//while (!bSuccess) {
		//	val *= 100;
		//	queryExtent = FVector(val, val, val);
		//	bSuccess = navSystem->ProjectPointToNavigation(targetLocation, navLoc, queryExtent);
		//	// makingg sure no infinite loop
		//	if (val >= 999999.0f) {
		//		UE_LOG(LogTemp, Display, TEXT("inf loop we out FIXASAP"));
		//	}
		//}
		//UE_LOG(LogTemp, Display, TEXT("Orig: %s, New: %s, same? %d"), *targetLocation.ToString(), *navLoc.Location.ToString(), targetLocation == navLoc.Location);
		// only comparing x and y bcuz projectpointtonavig modifies z everytime
		// goal: if player is unreachable position, enemy will go in front of player and scream
		//FVector newTargetLocation = navLoc.Location;
		//AController* targetPawnController;
		//FVector relativeVector;
		//if (APawn* targetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("targetPlayer")))) {
		//	targetPawnController = targetPawn->GetController();
		//	FRotator pawnRotation = targetPawnController->GetControlRotation();

		//}
		////OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), newTargetLocation);
		//result = Super::ExecuteTask(OwnerComp, NodeMemory);
		//if (result == EBTNodeResult::Succeeded) { // we have arrived, time to make the AI'S head turn and play montage
		//	FRotator AIRotation = controlledPawn->GetController()->GetControlRotation();
		//	AIRotation.Yaw = relativeVector.Rotation().Yaw + 180;
		//	controlledPawn->GetController()->SetControlRotation(AIRotation);
		//}
		//return result;
		
	}
	return result;
	*/
	//UE_LOG(LogTemp, Display, TEXT("Failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	//MoveToLocation(OwnerComp, NavLoc.Location);
}

FVector UBTTask_MoveToClosestLocation::getClosestNavigablePoint(FVector targetLocation)
{
	return FVector::ZeroVector;
	// todo

}
