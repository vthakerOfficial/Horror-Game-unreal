// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "EnemyAIController.h"
#include <Perception/PawnSensingComponent.h>
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));

}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	pawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAICharacter::onSeePawn);

}

void AEnemyAICharacter::onSeePawn(APawn* seenPawn)
{
	if (!seenPawn) return;

	if (seenPawn->ActorHasTag(TEXT("Player"))) {
		//UE_LOG(LogTemp, Display, TEXT("Found Player"));
		if (AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController())) {
			//UE_LOG(LogTemp, Display, TEXT("Found Player Controller, we now modifying playerlocation"));
			AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("targetPlayer"), seenPawn);
			GetWorldTimerManager().SetTimer(
				resumeWanderingTimerHandle,
				this,
				&AEnemyAICharacter::resumeWanderingCallbackFunc,
				pawnSensing->SensingInterval + resumeWanderingDelay,
				true
			);
		}
	}
	//else {
	//	//UE_LOG(LogTemp, Display, TEXT("Couldnt see the tag of player"));
	//}
}

void AEnemyAICharacter::resumeWanderingCallbackFunc()
{
	UE_LOG(LogTemp, Display, TEXT("CallbackFunc has been called"));
	if (AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController())) {
		UE_LOG(LogTemp, Display, TEXT("Found AIController, clearing value"));
		AIController->GetBlackboardComponent()->ClearValue(TEXT("playerLocation"));
	}
}

// Called every frame
void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

