// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/NavigationSystemBase.h"
#include "HorrorGameCharacter.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT("Update Player Location");
	//bNotifyBecomeRelevant = true;
	//bNotifyCeaseRelevant = true;
}

void UBTService_UpdatePlayerLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	//auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	//if (APawn* targetPawn = Cast<APawn>(blackBoardComp->GetValueAsObject(TEXT("targetPlayer")))) {
	//	if (AHorrorGameCharacter* targetCharacter = Cast<AHorrorGameCharacter>(targetPawn)) {
	//		//UE_LOG(LogTemp, Display, TEXT("HasBecomeRelevant"));
	//		targetCharacter->shakeCamera(60*60); // huge val (1hr)
	//	}
	//}
}

void UBTService_UpdatePlayerLocation::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	//auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	//if (APawn* targetPawn = Cast<APawn>(blackBoardComp->GetValueAsObject(TEXT("targetPlayer")))) {
	//	if (AHorrorGameCharacter* targetCharacter = Cast<AHorrorGameCharacter>(targetPawn)) {
	//		UE_LOG(LogTemp, Display, TEXT("HasStoppedBeingRelevant"));
	//		targetCharacter->shakeCamera(-1); // disabling camera shake
	//	}
	//}
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	if (APawn* targetPawn = Cast<APawn>(blackBoardComp->GetValueAsObject(TEXT("targetPlayer")))) {
		blackBoardComp->SetValueAsVector(TEXT("targetPlayerLocation"), targetPawn->GetActorLocation());
	}
}
