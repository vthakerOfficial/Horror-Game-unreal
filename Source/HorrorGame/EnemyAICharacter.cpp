// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "EnemyAIController.h"
#include <Perception/AIPerceptionComponent.h>
#include "BehaviorTree/BlackboardComponent.h"
//#include <Perception/AIPerceptionTypes.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Kismet/GameplayStatics.h>
#include "GameFramework/DamageType.h"
#include "HorrorGameCharacter.h"


//#include "TimerManager.h"


float AEnemyAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageTaken = DamageAmount > health ? 0 : DamageAmount;
	health -= damageTaken;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("AIHealth is %f"), health));
	return damageTaken;
}

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();

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

float AEnemyAICharacter::attackPlayer()
{
	if (bIsAttacking) return -1;
	// turngint towards nearest player


	// doing sphere trace to check if any single player is hittable
	TArray<FHitResult> outHits;
	const bool bHit = doSphereTrace(outHits);

	// ensuring no duplicates
	bool bCanHit = false;
	bool bAngry = false;
	TArray<AHorrorGameCharacter*> safeHitCharacters;
	if (bHit) {
		for (FHitResult& hitResult : outHits) {
			AHorrorGameCharacter* hitCharacter = Cast<AHorrorGameCharacter>(hitResult.GetActor());
			if (!hitCharacter) continue;

			bAngry = true;
			if (!hitCharacter->isSafe()) {
				bCanHit = true;
				break;
			}
			else {
				safeHitCharacters.Add(hitCharacter);
			}
		}
	}
	if (bCanHit) {
		bIsAttacking = true;
		float attackMontageDuration = -1;
		if (attackMontage) {
			PlayAnimMontage(attackMontage);
			attackMontageDuration = attackMontage->GetPlayLength() * attackMontageMultiplier;
		}
		
		GetWorldTimerManager().SetTimer(
			attackPlayerTimerHandle,
			this,
			&AEnemyAICharacter::attackPlayerCallbackFunc,
			attackMontageDuration,
			false
		);
		return attackMontageDuration;
	}
	else if (bAngry) { // our sphere trace found a player but they are safe
		float angryMontageDuration = -1;
		// turning towards a random player who is safe before playing montage so they get the full experience!
		if (AHorrorGameCharacter* randomSafeCharacter = safeHitCharacters[FMath::RandRange(0, safeHitCharacters.Num() - 1)]) {
			FVector characterLocation = randomSafeCharacter->GetActorLocation();
			FVector myLocation = GetActorLocation();

			FVector difference = characterLocation - myLocation;
			difference.Normalize();

			FQuat rotation = FQuat::FindBetweenNormals(FVector::ForwardVector, difference);
			FRotator newRotation = rotation.Rotator();
			newRotation.Roll = randomSafeCharacter->GetControlRotation().Roll;
			SetActorRotation(newRotation);
			newRotation.Yaw += 180;
			if (AController* characterController = randomSafeCharacter->GetController()) {
				characterController->ClientSetRotation(newRotation);
			}

		}


		if (angryMontage) {
			PlayAnimMontage(angryMontage);
			angryMontageDuration = angryMontage->GetPlayLength();
		}
		return angryMontageDuration;
	}
	return -1;






}


void AEnemyAICharacter::attackPlayerCallbackFunc()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("In Callback Func")));
	TArray<FHitResult> outHits;
	const bool bHit = doSphereTrace(outHits);

	bool bSuccess = false;
	if (bHit) {
		// ensuring no duplicates
		TSet<AActor*> alreadyHitActors;
		for (FHitResult& hitResult : outHits) {
			AHorrorGameCharacter* hitCharacter = Cast<AHorrorGameCharacter>(hitResult.GetActor());
			if (!hitCharacter) continue;

			if (!hitCharacter->isSafe()) {
				UGameplayStatics::ApplyDamage(hitCharacter, damageAmount, GetInstigatorController(), this, UDamageType::StaticClass());
				alreadyHitActors.Add(hitCharacter);
			}
		}
	}

	// allow public attackPlayer method to be called again
	bIsAttacking = false;

}

bool AEnemyAICharacter::doSphereTrace(TArray<FHitResult>& outHits)
{
	// SPHERE Trace

	FVector start = GetActorLocation();
	FVector end = GetActorLocation() + GetActorRotation().Vector() * attackOffset;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;
	objectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		start,
		end,
		sphereTraceRadius,
		objectTypesArray,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForDuration,
		outHits,
		true
	);
	return bHit;
}
