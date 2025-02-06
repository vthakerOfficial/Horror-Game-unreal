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
		pin = -1; 
		UE_LOG(LogTemp, Display, TEXT("---ERRORFIXNOW createNewPin (cppkeypad class), is being called with a value less than 1-------------"));
		return;
	}
	pin = 1234;	// delete this line
	//pin = FMath::RandRange(0, (int(FMath::Pow(10.0f, numDigits)))-1 );
}

TArray<int> AKeypad::getPinAsArray() const
{
	TArray<int32> result;
	if (pin < 0) return result;
	
	int32 t_Pin = pin;
	while (t_Pin > 0) {
		int32 item = t_Pin % 10;
		result.Insert(item, 0);
		t_Pin /= 10;
	}

	return result;
}

int32 AKeypad::getPin() const
{
	return pin;
}

void AKeypad::setIdentity(int32 newIdentity)
{
	identity = newIdentity;
}

int32 AKeypad::getIdentity() const
{
	return identity;
}


bool AKeypad::tryPin(int32 guess) const
{
	return guess == pin;
}

