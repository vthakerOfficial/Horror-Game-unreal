// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_LessOldWander.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UBTTask_LessOldWander : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_LessOldWander();
	void resetWanderLogic();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type myMove(AAIController* AIController);
	void findNewTargetLocation(UBehaviorTreeComponent& OwnerComp);
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	double wanderRadius = 500;
	FNavLocation targetNavLocation;
};
