// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StructItemInfo.h"


#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORGAME_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Interface")
	FStructItemInfo pickUp();


	//UFUNCTION(BlueprintNativeEvent, Category = "Interface")
	//void drop(AActor* actor);

	//UFUNCTION(BlueprintNativeEvent, Category = "Interface")
	//void equip(AActor* actor);

	//UFUNCTION(BlueprintNativeEvent, Category = "Interface")
	//void unequip(AActor* actor);

	//void onPickedUp_Implementation(AActor* other) {
	//	// nth
	//}
};
