// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDropped.generated.h"

UCLASS()
class HORRORGAME_API AItemDropped : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDropped();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void initialize();
	UFUNCTION(BlueprintImplementableEvent)
	void equipped();
	UFUNCTION(BlueprintImplementableEvent)
	void unequipped();
};
