// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyAICharacter.h"
#include <Perception/AISenseConfig_Sight.h>
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"



//void AEnemyAIController::BeginPlay()
//{
//	Super::BeginPlay();
//}

AEnemyAIController::AEnemyAIController()
{
	setupPerceptionSystem();
	//GetPerceptionComponent
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AEnemyAICharacter* character = Cast<AEnemyAICharacter>(GetPawn())) {
		character->Tags.Add(TEXT("AI"));
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(AIBehavior);
}

void AEnemyAIController::onActorDetected(AActor* detectedActor, FAIStimulus stimulus)
{
	ETeamAttitude::Type attitude = GetTeamAttitudeTowards(*detectedActor);
	if (attitude != ETeamAttitude::Hostile || !stimulus.IsValid()) return;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("AI Has Seen Player"));
	}
	GetBlackboardComponent()->SetValueAsObject(TEXT("targetPlayer"), detectedActor);
}

void AEnemyAIController::onActorForgotten(AActor* forgottenActor)
{
	ETeamAttitude::Type attitude = GetTeamAttitudeTowards(*forgottenActor);
	if (attitude != ETeamAttitude::Hostile) return;
	resumeWanderingCallbackFunc();
	/*GetWorldTimerManager().SetTimer(
		resumeWanderingTimerHandle,
		this,
		&AEnemyAIController::resumeWanderingCallbackFunc,
		perception->GetComponentTickInterval() + resumeWanderingDelay,
		false
	);*/
}


void AEnemyAIController::resumeWanderingCallbackFunc() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("AI is returning to Wandering"));
	}

	GetBlackboardComponent()->ClearValue(TEXT("targetPlayer"));
	GetBlackboardComponent()->ClearValue(TEXT("targetPlayerLocation"));
}

void AEnemyAIController::setupPerceptionSystem()
{
	perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*perception);
	if (UAISenseConfig_Sight* sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"))) {
		perception->ConfigureSense(*sightConfig);
		perception->SetDominantSense(*sightConfig->GetSenseImplementation());
		perception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::onActorDetected);
		perception->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyAIController::onActorForgotten);
			//.AddDynamic(this, &AEnemyAIController::onActorForgotten);
	}
}
ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& other) const
{
	return other.ActorHasTag("Player") ? ETeamAttitude::Hostile : (other.ActorHasTag("AI") ? ETeamAttitude::Friendly : ETeamAttitude::Neutral);

	//if (other.ActorHasTag("Player")) {
	//	return ETeamAttitude::Hostile;
	//}
	//else if (other.ActorHasTag("AI")) {
	//	return ETeamAttitude::Friendly;
	//}
	//return ETeamAttitude::Neutral;
	
}

