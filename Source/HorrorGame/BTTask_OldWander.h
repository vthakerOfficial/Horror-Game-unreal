// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_OldWander.generated.h"
struct MyTaskMemory
{
	FVector targetLocation;
	bool bIsChasingPlayer;
};
/**
 * 
 */
UCLASS()
class HORRORGAME_API UBTTask_OldWander : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_OldWander();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, Category="AI")
	double wanderRadius = 500;
};
