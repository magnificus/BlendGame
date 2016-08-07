// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotsGameMode.h"
#include "RobotsHUD.h"
#include "RobotsCharacter.h"
#include "Engine.h"


ARobotsGameMode::ARobotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/robotdude/RobotChar"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ARobotsHUD::StaticClass();



}

void ARobotsGameMode::RestartLevel() {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Starting level house");
	GetWorld()->ServerTravel("World'/Game/maps/house.house?Listen");
}
