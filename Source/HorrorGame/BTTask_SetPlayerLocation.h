// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UBTTask_SetPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SetPlayerLocation();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
