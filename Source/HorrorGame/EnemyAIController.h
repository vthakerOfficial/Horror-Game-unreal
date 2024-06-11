// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	//virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	//virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* AIBehavior;

};
