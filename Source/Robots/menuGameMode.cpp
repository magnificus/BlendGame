// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "menuGameMode.h"



AmenuGameMode::AmenuGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/maps/menuCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


}


void AmenuGameMode::HostGame()
{
	GetWorld()->ServerTravel("/Game/maps/lobbyLevel?Listen", true);
}



void AmenuGameMode::JoinGame(FString address) {
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientTravel(address, TRAVEL_Absolute);
}