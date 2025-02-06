// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelOne.h"
#include <Kismet/GameplayStatics.h>
#include "Keypad.h"
#include "Keypad_Note.h"


void ALevelOne::BeginPlay()
{
	// set all keypad codes
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKeypad::StaticClass(), foundActors);

	for (int i = 0; i < foundActors.Num(); i++) {

		AKeypad* keypad = Cast<AKeypad>(foundActors[i]);
		if (!keypad) continue;

		keypad->createNewPin(4);
	

		TArray<AActor*> foundActors1;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKeypad_Note::StaticClass(), foundActors1);
		// filtering out notes with different identity than keypad's
		int32 keypadIdentity = keypad->getIdentity();
		for (int j = 0; j < foundActors1.Num(); j++) {
			AKeypad_Note* keypadNote = Cast<AKeypad_Note>(foundActors1[i]);
			if (!keypadNote || keypadNote->getIdentity() != keypadIdentity) {
				foundActors1.RemoveAt(j);
				j--;
			}
		}


		int notesSize = foundActors1.Num();
		TArray<int> vals = keypad->getPinAsArray();
		if (notesSize < vals.Num()) {
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Not enough notes for keypad with identity of: %d"), keypadIdentity));
			continue;
		}




		TArray<bool> visited;
		visited.Init(false, notesSize);
		for (int j = 0; j < vals.Num(); j++) {
			while (true) {
				int32 possibleIndex = FMath::RandRange(0, notesSize-1);
				if (visited[possibleIndex]) continue;

				visited[possibleIndex] = true;

				AKeypad_Note* keypadNote = Cast<AKeypad_Note>(foundActors1[possibleIndex]);
				//if (!keypadNote) continue; // alr did check earlier

				keypadNote->setValueAndIndex(vals[j], j);
				break;
			}
		}
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, FString::Printf(TEXT("Pin: %d"), keypad->getPin()));

	}

}
