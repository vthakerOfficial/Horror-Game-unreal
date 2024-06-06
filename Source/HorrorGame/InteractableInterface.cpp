// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

void IInteractableInterface::interact(AActor* actor)
{
	UE_LOG(LogTemp, Display, TEXT("Interface method: \"interact\" has run"));
}
