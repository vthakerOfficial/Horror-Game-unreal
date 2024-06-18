// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyAICharacter.h"
#include <Perception/AISenseConfig_Sight.h>
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HorrorGameCharacter.h"



//void AEnemyAIController::BeginPlay()
//{
//	Super::BeginPlay();
//}

AEnemyAIController::AEnemyAIController()
{
	setupPerceptionSystem();
	//GetPerceptionComponent
}

float AEnemyAIController::getPerceptionMaxAge() const
{
	if (UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(
		perception->GetSenseConfig(UAISense::GetSenseID<UAISense_Sight>()))) {
		return sightConfig->GetMaxAge();
	}
	return -1;
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
	if (AHorrorGameCharacter* player = Cast<AHorrorGameCharacter>(GetBlackboardComponent()->GetValueAsObject(TEXT("targetPlayer")))) {
		player->shakeCamera(60*60);
	}
}

void AEnemyAIController::onActorForgotten(AActor* forgottenActor)
{
	ETeamAttitude::Type attitude = GetTeamAttitudeTowards(*forgottenActor);
	if (attitude != ETeamAttitude::Hostile) return;
	resumeWanderingCallbackFunc();
}


void AEnemyAIController::resumeWanderingCallbackFunc() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("AI is returning to Wandering"));
	}
	if (AHorrorGameCharacter* player = Cast<AHorrorGameCharacter>(GetBlackboardComponent()->GetValueAsObject(TEXT("targetPlayer")))) {
		player->shakeCamera(-1);
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

