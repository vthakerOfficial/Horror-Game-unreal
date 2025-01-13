// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ItemInterface.h"

#include "Keypad_Note.generated.h"

UCLASS()
class HORRORGAME_API AKeypad_Note : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeypad_Note();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 identity = -1;

	int32 getIdentity() const { return identity; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void setValueAndIndex(int newVal, int newIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int val = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int index = -1;

};
