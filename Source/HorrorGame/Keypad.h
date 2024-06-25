// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Keypad.generated.h"

UCLASS()
class HORRORGAME_API AKeypad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeypad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void createNewPin(int32 numDigits);

	UFUNCTION(BlueprintPure)
	bool tryPin(int32 guess);
private:
	int32 passcode;
};
