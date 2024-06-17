// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"
#include "EnemyAICharacter.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
	NodeName = TEXT("Attack Player");
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	// checking for LOS b4 continuing
	TArray<AActor*> playerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), playerControllers);
	bool bSuccess = false;
	for (AActor* playerController : playerControllers) {
		if (AIController->LineOfSightTo(playerController)) {
			bSuccess = true;
			break;
		}
	}
	if (!bSuccess) return EBTNodeResult::Failed;

	AEnemyAICharacter* AICharacter = Cast<AEnemyAICharacter>(AIController->GetPawn());
	if (!AICharacter) return EBTNodeResult::Failed;



	float attackDuration = AICharacter->attackPlayer();
	if (attackDuration > 0.0f) {
		ownerCompRef = &OwnerComp;
		GetWorld()->GetTimerManager().SetTimer(
			sleepTimerHandle,
			this,
			&UBTTask_AttackPlayer::sleepTimerCallbackFunc,
			attackDuration,
			false
		);
		return EBTNodeResult::InProgress;
	}
	else {
		return EBTNodeResult::Succeeded;
	}

}

void UBTTask_AttackPlayer::sleepTimerCallbackFunc()
{
	FinishLatentTask(*ownerCompRef, EBTNodeResult::Succeeded);
}