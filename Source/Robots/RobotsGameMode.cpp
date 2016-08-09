// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotsGameMode.h"
#include "RobotsHUD.h"
#include "RobotCharacter.h"
#include "RobotPlayerState.h"
#include "Engine.h"


ARobotsGameMode::ARobotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/robotdude/RobotChar"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ARobotsHUD::StaticClass();
	PlayerStateClass = ARobotPlayerState::StaticClass();



}

void ARobotsGameMode::RestartLevel() {
	GetWorld()->ServerTravel("/Game/maps/house?Listen");
}

void ARobotsGameMode::PlayerDeath() {

	int32 aliveCount = 0;
	for (TObjectIterator<ARobotCharacter> Itr; Itr; ++Itr)
	{
		// Access the subclass instance with the * or -> operators.
		ARobotCharacter *robot = *Itr;

		if (robot->alive) {
			aliveCount++;
		}
	}

	if (aliveCount <= 1) {
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &ARobotsGameMode::RestartLevel, 3, false);
		RestartLevel();
	}
}