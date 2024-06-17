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
public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void setupPerceptionSystem();


	// AI Perception Related
	UFUNCTION() virtual void onActorDetected(AActor* detectedActor, FAIStimulus stimulus);
	UFUNCTION() virtual void onActorForgotten(AActor* forgottenActor);

	void resumeWanderingCallbackFunc();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& other) const override;
	//virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* AIBehavior;

	//UPROPERTY(EditAnywhere, Category = "AI")
	//float resumeWanderingDelay = 3.0f;

	class UAIPerceptionComponent* perception;
	FTimerHandle resumeWanderingTimerHandle;
};
