// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToClosestLocation.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UBTTask_MoveToClosestLocation : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_MoveToClosestLocation();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FVector getClosestNavigablePoint(FVector targetLocation);

};
