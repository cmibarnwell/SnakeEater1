// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SnakeEater1Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"

//////////////////////////////////////////////////////////////////////////
// ASnakeEater1Character

ASnakeEater1Character::ASnakeEater1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Initialize Health and Shield
	Health = 1.0;
	Shield = 1.0;

	// Init bDead
	bDead = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FName fnHeadSocket = TEXT("head");
	FollowCamera->SetupAttachment(GetMesh(), fnHeadSocket); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ASnakeEater1Character::BeginPlay()
{
	Super::BeginPlay();

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FString("Health: ") + FString::SanitizeFloat(Health));

	if (wFPSHUD) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyFPSHUD = CreateWidget<UUserWidget>(GetWorld(), wFPSHUD);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyFPSHUD)
		{
			//let add it to the view port
			MyFPSHUD->AddToViewport();
		}
	}
}

void ASnakeEater1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Shield < 1)
		Shield += .001;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASnakeEater1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASnakeEater1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASnakeEater1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASnakeEater1Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASnakeEater1Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASnakeEater1Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASnakeEater1Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASnakeEater1Character::OnResetVR);
}


void ASnakeEater1Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASnakeEater1Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ASnakeEater1Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ASnakeEater1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASnakeEater1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASnakeEater1Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASnakeEater1Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASnakeEater1Character::DealDamage(float DMG)
{
	//Should not use C expressions as flow control. 
	//Also, something here is dereferencing a nullptr to (this)
	if (Shield >= 0)
	{
		Shield -= DMG;
	}
	else 
	{
		Health -= DMG;
	}
	
	if (wDamageFX) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyDamageFX = CreateWidget<UUserWidget>(GetWorld(), wDamageFX);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyDamageFX)
		{
			//let add it to the view port
			MyDamageFX->AddToViewport();
		}
	}

	if (Health <= 0.0) {
		Death();
	}
}

void ASnakeEater1Character::Heal(float h)
{
	Health + h >= 1 ? Health = 1 : Health += h;
}

void ASnakeEater1Character::Death()
{
	/*
	AController* PC = GetController();

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	if (wDeathScreen) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyDeathScreen = CreateWidget<UUserWidget>(GetWorld(), wDeathScreen);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyDeathScreen)
		{
			//let add it to the view port
			MyDeathScreen->AddToViewport();
		}
	}*/

	bDead = true;
}
