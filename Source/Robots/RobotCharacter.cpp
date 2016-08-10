// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotCharacter.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "RobotsGameMode.h"


//////////////////////////////////////////////////////////////////////////
// ARobotCharacter

ARobotCharacter::ARobotCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

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
	//CameraBoom->AddLocalOffset(FVector(0, 0, 20));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

												   // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
												   // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	PunchZone = CreateDefaultSubobject<UBoxComponent>(TEXT("PunchZone"));
	PunchZone->SetupAttachment(RootComponent);



	isPunching = false;
	alive = true;
	health = 100;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARobotCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ARobotCharacter::FirePressed);
	InputComponent->BindAction("Fire", IE_Released, this, &ARobotCharacter::FireReleased);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ARobotCharacter::SprintPressed);
	InputComponent->BindAction("Sprint", IE_Released, this, &ARobotCharacter::SprintReleased);

	InputComponent->BindAxis("MoveForward", this, &ARobotCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARobotCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ARobotCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ARobotCharacter::LookUpAtRate);

	InputComponent->BindAction("Start Game", IE_Pressed, this, &ARobotCharacter::RestartPressed);


	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ARobotCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ARobotCharacter::TouchStopped);

	isPunching = false;
	alive = true;
}

void ARobotCharacter::RestartPressed() {
	APlayerController* controller = (APlayerController*) GetController();
	GetWorld()->ServerTravel("/Game/maps/house?Listen");
}

//void ARobotCharacter::ToLobbyPressed() {
//	APlayerController* controller
//}


// sprinting
void ARobotCharacter::SprintPressed() {
	SetSpeed(600);
}

void ARobotCharacter::SprintReleased() {
	SetSpeed(300);
}


void ARobotCharacter::SetSpeed(float newSpeed)
{
	speed = newSpeed;
	GetCharacterMovement()->MaxWalkSpeed = speed;

	if (Role < ROLE_Authority) {
		ServerSetSpeed(newSpeed);
	}
}

bool ARobotCharacter::ServerSetSpeed_Validate(float newSpeed) {
	return true;
}

void ARobotCharacter::ServerSetSpeed_Implementation(float newSpeed) {
	SetSpeed(newSpeed);
}

// punching

void ARobotCharacter::SetIsPunching(bool newIsPunching) {
	isPunching = newIsPunching;
	if (Role < ROLE_Authority) {
		ServerSetIsPunching(newIsPunching);
	}
}


bool ARobotCharacter::ServerSetIsPunching_Validate(bool newIsPunching) {
	return true;
}

void ARobotCharacter::ServerSetIsPunching_Implementation(bool newIsPunching) {
	SetIsPunching(newIsPunching);
}

void ARobotCharacter::SetIsPunchingFromBP(bool newIsPunching) {
	SetIsPunching(newIsPunching);
}

// alive

void ARobotCharacter::SetIsAlive(bool newIsAlive) {
	alive = newIsAlive;

	if (Role < ROLE_Authority) {
		ServerSetIsAlive(newIsAlive);
	}

	if (!alive) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Player Death!");
		ARobotsGameMode* g = (ARobotsGameMode*)GetWorld()->GetAuthGameMode();
		g->PlayerDeath();
	}

}

bool ARobotCharacter::ServerSetIsAlive_Validate(bool newIsAlive) {
	return true;
}

void ARobotCharacter::ServerSetIsAlive_Implementation(bool newIsAlive) {
	SetIsAlive(newIsAlive);

}

void ARobotCharacter::FirePressed() {
	if (alive)
		SetIsPunching(true);
}

void ARobotCharacter::FireReleased() {
	SetIsPunching(false);
}

void ARobotCharacter::SetHealth(float newHealth)
{
	// Change the value of the bSomeBool property
	health = newHealth;

	// If this next check succeeds, we are *not* the authority, meaning we are a network client.
	// In this case we also want to call the server function to tell it to change the bSomeBool property as well.
	if (Role < ROLE_Authority)
	{
		ServerSetHealth(newHealth);
	}
}

bool ARobotCharacter::ServerSetHealth_Validate(float health)
{
	return true;
}

void ARobotCharacter::ServerSetHealth_Implementation(float newHealth)
{
	// This function is only called on the server (where Role == ROLE_Authority), called over the network by clients.
	// We need to call SetSomeBool() to actually change the value of the bool now!
	// Inside that function, Role == ROLE_Authority, so it won't try to call ServerSetSomeBool() again.
	SetHealth(newHealth);
}


void ARobotCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARobotCharacter, isPunching);
	DOREPLIFETIME(ARobotCharacter, health);
	DOREPLIFETIME(ARobotCharacter, speed);
	DOREPLIFETIME(ARobotCharacter, alive);
}

void ARobotCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ARobotCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ARobotCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARobotCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void ARobotCharacter::MoveForward(float Value)
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

void ARobotCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
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
