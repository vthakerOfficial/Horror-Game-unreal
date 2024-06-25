// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorGameCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Components/SpotLightComponent.h>
#include "Misc/OutputDeviceNull.h"
#include "InteractableInterface.h"
#include "Kismet/GameplayStatics.h"
#include <AIController.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AHorrorGameCharacter

float AHorrorGameCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float damageTaken = DamageAmount > health ? 0 : DamageAmount;
	health -= damageTaken;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Player Health is %f"), health));
	return damageTaken;
}




bool AHorrorGameCharacter::isSafe() const
{
	return bIsSafe;
}

void AHorrorGameCharacter::setIsSafe(bool bNewIsSafe)
{
	bIsSafe = bNewIsSafe;
}

AHorrorGameCharacter::AHorrorGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), TEXT("head"));
	//CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	flashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	flashLight->SetupAttachment(FollowCamera, USpringArmComponent::SocketName);		


	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AHorrorGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// settings its key
	Tags.AddUnique(FName("Player"));
	//cameraShakeClass = 

	// settings its Team (so AI knows to attack this)
	//FGenericTeamId

}

bool AHorrorGameCharacter::takeKey(int32 keyID)
{
	if (keyID == -1) return true; // -1 = door is alr open. Doing it here cuz blueprint slow and I don't want to complicate things there.
	if (doorKeys.Contains(keyID)) {
		doorKeys.Remove(keyID);
		//keyIDs.RemoveAll(keyID);
		return true;
	}
	return false;
}


void AHorrorGameCharacter::shakeCamera_Implementation(float duration)
{
	//empty
}

//bool AHorrorGameCharacter::myShakeCamera(float duration)
//{
//	return false;
//}









//////////////////////////////////////////////////////////////////////////
// Input

void AHorrorGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Look);

		// Flashlight
		EnhancedInputComponent->BindAction(flashLightAction, ETriggerEvent::Started, this, &AHorrorGameCharacter::toggleFlashLight);

		// Interact
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Started, this, &AHorrorGameCharacter::interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHorrorGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHorrorGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHorrorGameCharacter::toggleFlashLight(const FInputActionValue& ignoredValue)
{
	bool bNewVisibility = !flashLight->IsVisible();
	flashLight->SetVisibility(bNewVisibility);
}

void AHorrorGameCharacter::interact(const FInputActionValue& ignoredValue)
{
	// only closet rn but will just interact with any subclass of InteractableInterface
	TArray<AActor*> overlappingActors;

	TSubclassOf<IInteractableInterface> interfaceClass;
	GetOverlappingActors(overlappingActors);



	for (AActor* overlappingActor : overlappingActors) {
		IInteractableInterface* interactableActor = Cast<IInteractableInterface>(overlappingActor);
		if (!interactableActor) continue;
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("sucessfully interacted")));
		//if (!GetController()->LineOfSightTo(overlappingActor)) continue;

		FHitResult hitResult;
		FVector startLoc = GetActorLocation();
		FVector endLoc = startLoc + GetControlRotation().Vector() * 5000.0f;
		FCollisionQueryParams params;
		params.AddIgnoredActor(GetController()->GetPawn());
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECC_Visibility, params);
		if (!bHit) return;

		
		if (IInteractableInterface* hitInteractableActor = Cast<IInteractableInterface>(hitResult.GetActor())) {
			IInteractableInterface::Execute_interact(overlappingActor, this);
		}

		
	}
}
