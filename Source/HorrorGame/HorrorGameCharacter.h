// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDeviceNull.h"
#include "GenericTeamAgentInterface.h"

#include "HorrorGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USpotLightComponent;
struct FInputActionValue;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHorrorGameCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool isSafe() const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void setIsSafe(bool isSafe);
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpotLightComponent* flashLight;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* flashLightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* interactAction;

public:
	AHorrorGameCharacter();
	
	// AI Perception Related
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") 
	int32 ID = 0;

	virtual FGenericTeamId GetGenericTeamId() const override {
		return teamId;
	}

protected:
	// taking/applying damage stuff
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditAnywhere)
	float damageAmount = 10.0f;
	UPROPERTY(EditAnywhere)
	float health = 100.0f;


	FGenericTeamId teamId;

	// User Input funcs

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void toggleFlashLight(const FInputActionValue& value);
			
	void interact(const FInputActionValue& value);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fear")
	void shakeCamera(float duration);

	UFUNCTION(BlueprintCallable)
	bool takeKey(int32 keyID);

private:
	bool bIsSafe = false;

	TArray<int32> doorKeys;

};

