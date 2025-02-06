// Fill out your copyright notice in the Description page of Project Settings.


#include "Keypad_Note.h"

// Sets default values
AKeypad_Note::AKeypad_Note()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AKeypad_Note::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeypad_Note::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeypad_Note::setValueAndIndex_Implementation(int newVal, int newIndex)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("cPP")));
	val = newVal; index = newIndex;
}

