// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "menuGameMode.h"



AmenuGameMode::AmenuGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/maps/menuCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/robotdude/RobotControllerBP"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;

}


void AmenuGameMode::ExecuteFunction(FString parameter)
{
	if (parameter.Equals("host")) {
		HostGame();
	} else if (parameter.Equals("join")){
		ARobotController* c = (ARobotController*) UGameplayStatics::GetPlayerController(GetWorld(), 0);
		c->showJoinWidget();

	} else if (parameter.Equals("quit")){
		FGenericPlatformMisc::RequestExit(false);
	}
}

void AmenuGameMode::HostGame()
{
	GetWorld()->ServerTravel("/Game/maps/lobbyLevel?Listen", true);
}



void AmenuGameMode::JoinGame(FString address) {
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientTravel(address, TRAVEL_Absolute);
}