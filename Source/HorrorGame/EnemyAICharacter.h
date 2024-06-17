// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"

UCLASS()
class HORRORGAME_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;



public:
	// Sets default values for this character's properties
	AEnemyAICharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float attackPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION() virtual void attackPlayerCallbackFunc();

	bool bIsAttacking = false;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditAnywhere)
	float damageAmount = 10.0f;
	UPROPERTY(EditAnywhere)
	float health = 100.0f;

	UPROPERTY(EditAnywhere) float attackOffset = 100.0;
	UPROPERTY(EditAnywhere) float sphereTraceRadius = 100.0f;

	virtual bool doSphereTrace(TArray<FHitResult>& outHits);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* attackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* angryMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	float attackMontageMultiplier = .5f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	//float attackMontageDuration = 0.0f;

	FTimerHandle attackPlayerTimerHandle;

	

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UPawnSensingComponent* pawnSensing;
	//class UAIPerceptionComponent* perception;
	//FTimerHandle resumeWanderingTimerHandle;
	//UPROPERTY(EditAnywhere, Category = "Wandering")
	//float resumeWanderingDelay = 1.0f;

	//FTimerHandle resumeWanderingTimerHandle;

};
