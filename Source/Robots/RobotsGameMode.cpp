// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotsGameMode.h"
#include "RobotsHUD.h"
#include "RobotsCharacter.h"

ARobotsGameMode::ARobotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
<<<<<<< HEAD
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/RobotChar"));
=======
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
>>>>>>> f9d5048e8ebff98438f81ccb8b4b11dcd708af01
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARobotsHUD::StaticClass();
}
