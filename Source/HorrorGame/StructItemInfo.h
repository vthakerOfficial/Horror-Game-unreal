#pragma once

#include "CoreMinimal.h"

#include "Engine/Texture2D.h"
#include "UObject/SoftObjectPtr.h"

#include "StructItemInfo.generated.h"

USTRUCT(BlueprintType)
struct FStructItemInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString socketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> itemRef;
};