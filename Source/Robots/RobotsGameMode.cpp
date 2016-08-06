// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotsGameMode.h"
#include "RobotsHUD.h"
#include "RobotsCharacter.h"

ARobotsGameMode::ARobotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/robotdude/RobotChar"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARobotsHUD::StaticClass();
}
