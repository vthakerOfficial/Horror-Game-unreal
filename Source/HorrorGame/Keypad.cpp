// Fill out your copyright notice in the Description page of Project Settings.


#include "Keypad.h"

// Sets default values
AKeypad::AKeypad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AKeypad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeypad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeypad::createNewPin(int32 numDigits)
{
	if (numDigits < 1) {
		passcode = -1; 
		UE_LOG(LogTemp, Display, TEXT("---ERRORFIXNOW createNewPin (cppkeypad class), is being called with a value less than 1-------------"));
		return;
	}
	passcode = FMath::RandRange(0, (int(FMath::Pow(10.0f, numDigits)))-1 );
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("passcode: %d"), passcode));
}

bool AKeypad::tryPin(int32 guess)
{
	return guess == passcode;
}

