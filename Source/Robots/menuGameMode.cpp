// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "menuGameMode.h"
#include "RobotPlayerState.h"


AmenuGameMode::AmenuGameMode()
	: Super()
{

	PlayerStateClass = ARobotPlayerState::StaticClass();


}


void AmenuGameMode::ExecuteFunction(FString parameter)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, parameter);
	if (parameter.Equals("host_lab")) {
		HostGame("lab");
	}
	else if (parameter.Equals("host_nature")) {
		HostGame("nature");
	}
	else if (parameter.Equals("host_factory")) {
		HostGame("factory");
	}
	else if (parameter.Equals("join")){
		ARobotController* c = (ARobotController*) UGameplayStatics::GetPlayerController(GetWorld(), 0);
		c->showJoinWidget();

	} else if (parameter.Equals("quit")){
		FGenericPlatformMisc::RequestExit(false);
	}
}

void AmenuGameMode::HostGame(FString name)
{
	GetWorld()->ServerTravel("/Game/maps/" + name + "?Listen", true);
}



void AmenuGameMode::JoinGame(FString address) {
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientTravel(address, TRAVEL_Absolute);
}