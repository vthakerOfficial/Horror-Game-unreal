// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"

#include "Keypad.generated.h"

UCLASS()
class HORRORGAME_API AKeypad : public AActor, public IInteractableInterface
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
	bool tryPin(int32 guess) const;

	UFUNCTION(BlueprintPure)
	TArray<int> getPinAsArray() const;

	UFUNCTION(BlueprintPure)
	int32 getPin() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 identity = -1;

	void setIdentity(int32 newIdentity);
	int32 getIdentity() const;
private:
	int32 pin;
};
