// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotCharacter.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "RobotsGameMode.h"
#include "Activatable.h"


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

	canLaser = false;
	canAssimilate = false;
	canActivate = false;
	health = 100;
	standing = EStanding::GOOD;
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

	InputComponent->BindAction("Activate", IE_Pressed, this, &ARobotCharacter::Activate);


	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ARobotCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ARobotCharacter::TouchStopped);

	isPunching = false;
	alive = true;
}

void ARobotCharacter::RestartPressed() {
	if (Role < ROLE_Authority) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Not host, not allowed to restart");
		return;
	}
	APlayerController* controller = (APlayerController*)GetController();
	ARobotsGameMode* g = (ARobotsGameMode*)GetWorld()->GetAuthGameMode();
	g->RestartLevel(1);
}


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

// carrying

void ARobotCharacter::SetIsCarrying(bool newParam) {
	isCarrying = newParam;
	if (Role < ROLE_Authority) {
		ServerSetIsCarrying(newParam);
	}
}


bool ARobotCharacter::ServerSetIsCarrying_Validate(bool newParam) {
	return true;
}

void ARobotCharacter::ServerSetIsCarrying_Implementation(bool newParam) {
	SetIsCarrying(newParam);
}

// throwing

void ARobotCharacter::SetIsThrowing(bool newParam) {
	isThrowing = newParam;
	if (Role < ROLE_Authority) {
		ServerSetIsThrowing(newParam);
	}
}


bool ARobotCharacter::ServerSetIsThrowing_Validate(bool newParam) {
	return true;
}

void ARobotCharacter::ServerSetIsThrowing_Implementation(bool newParam) {
	SetIsThrowing(newParam);
}

// laser

void ARobotCharacter::SetCanLaser(bool newCanLaser) {
	canLaser = newCanLaser;
	if (Role < ROLE_Authority) {
		ServerSetCanLaser(newCanLaser);
	}
}


bool ARobotCharacter::ServerSetCanLaser_Validate(bool newCanLaser) {
	return true;
}

void ARobotCharacter::ServerSetCanLaser_Implementation(bool newCanLaser) {
	SetCanLaser(newCanLaser);
}

// assimilate

void ARobotCharacter::SetCanAssimilate(bool newParam) {
	canAssimilate = newParam;
	if (Role < ROLE_Authority) {
		ServerSetCanAssimilate(newParam);
	}
}


bool ARobotCharacter::ServerSetCanAssimilate_Validate(bool newParam) {
	return true;
}

void ARobotCharacter::ServerSetCanAssimilate_Implementation(bool newParam) {
	SetCanAssimilate(newParam);
}

// reveal

void ARobotCharacter::SetCanReveal(bool newParam) {
	canReveal = newParam;
	if (Role < ROLE_Authority) {
		ServerSetCanReveal(newParam);
	}
}


bool ARobotCharacter::ServerSetCanReveal_Validate(bool newParam) {
	return true;
}

void ARobotCharacter::ServerSetCanReveal_Implementation(bool newParam) {
	SetCanReveal(newParam);
}


// alive

void ARobotCharacter::SetIsAlive(bool newIsAlive) {
	alive = newIsAlive;

	if (Role < ROLE_Authority) {
		ServerSetIsAlive(newIsAlive);
	}

	if (!alive) {
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
	if (alive) {
		if (isCarrying) {
			SetIsThrowing(true);
			SetIsCarrying(false);
		}else{
			SetIsPunching(true);
		}

	}
}

void ARobotCharacter::FireReleased() {
	SetIsPunching(false);
}

void ARobotCharacter::SetHealth(float newHealth)
{
	health = newHealth;

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
	SetHealth(newHealth);
}


void ARobotCharacter::SetCanBomb(bool newParam)
{
	canBomb = newParam;

	if (Role < ROLE_Authority)
	{
		ServerSetCanBomb(newParam);
	}
}

bool ARobotCharacter::ServerSetCanBomb_Validate(bool newParam)
{
	return true;
}

void ARobotCharacter::ServerSetCanBomb_Implementation(bool newParam)
{
	SetCanBomb(newParam);
}

void ARobotCharacter::SetStanding(EStanding newParam)
{
	standing = newParam;

	if (Role < ROLE_Authority)
	{
		ServerSetStanding(newParam);
	}
}

bool ARobotCharacter::ServerSetStanding_Validate(EStanding newParam)
{
	return true;
}

void ARobotCharacter::ServerSetStanding_Implementation(EStanding newParam)
{
	SetStanding(newParam);
}


void ARobotCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARobotCharacter, isPunching);
	DOREPLIFETIME(ARobotCharacter, health);
	DOREPLIFETIME(ARobotCharacter, speed);
	DOREPLIFETIME(ARobotCharacter, alive);
	DOREPLIFETIME(ARobotCharacter, canLaser);
	DOREPLIFETIME(ARobotCharacter, canAssimilate);
	DOREPLIFETIME(ARobotCharacter, canReveal);
	DOREPLIFETIME(ARobotCharacter, canBomb);
	DOREPLIFETIME(ARobotCharacter, standing);
	DOREPLIFETIME(ARobotCharacter, isCarrying);
	DOREPLIFETIME(ARobotCharacter, isThrowing);

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


void ARobotCharacter::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	AActor* hitActor = getActorInFront();
	IActivatable* activatable = Cast<IActivatable>(hitActor);
	if (activatable) {
		canActivate = true;
		activatableName = activatable->GetName();
	}
	else {
		canActivate = false;
	}

}

AActor* ARobotCharacter::getActorInFront() {
	FVector Start = GetActorLocation() + FVector(0, 0, 64);
	FVector End = Start + FollowCamera->GetForwardVector() * 160;

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,        //result
		Start,    //start
		End, //end
		ECC_Pawn, //collision channel
		RV_TraceParams
	);

	return RV_Hit.GetActor();
}

void ARobotCharacter::Activate_Implementation() {
	AActor* actor = getActorInFront();
	auto a = Cast<IActivatable>(actor);
	if (a)
		a->Activate(this);
}

bool ARobotCharacter::Activate_Validate() {
	return true;
}

void ARobotCharacter::Exit() {

}