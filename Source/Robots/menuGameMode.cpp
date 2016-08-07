// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "menuGameMode.h"
#include "Engine.h"




AmenuGameMode::AmenuGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/maps/menuCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


}


void AmenuGameMode::HostGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Starting lobbylevel");
	GetWorld()->ServerTravel("/Game/maps/lobbyLevel");
}

void AmenuGameMode::ExecuteFunction(FString parameter) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Starting lobbylevel");
	if (parameter.Equals(FString("host"))) {
		HostGame();
	}
}
