// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotsGameMode.h"
#include "RobotsHUD.h"
#include "RobotCharacter.h"
#include "RobotPlayerState.h"
#include "Engine.h"
#include "ChatWidget.h"
#include "RobotGameState.h"
#include "Blueprint/UserWidget.h"
#include "RobotController.h"

void ARobotsGameMode::BeginPlay()
{
	Super::BeginPlay();



}

ARobotsGameMode::ARobotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/robotdude/RobotChar"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ARobotsHUD::StaticClass();
	PlayerStateClass = ARobotPlayerState::StaticClass();

	GameStateClass = ARobotGameState::StaticClass();
	PlayerControllerClass = ARobotController::StaticClass();

	restarting = false;



}
void ARobotsGameMode::K2_PostLogin()
{
	SendServerMessage(FText::FromString("Player Connected!"));
}
void ARobotsGameMode::RestartLevel(float delay) {
	restarting = true;
	FTimerHandle UnusedHandle;
	SendServerMessage(FText::FromString("Restarting!"));
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ARobotsGameMode::RestartLevel, delay, false);
	restarting = false;
}

void ARobotsGameMode::EnterLevel(FString name) {
	GetWorld()->ServerTravel("/Game/maps/" + name + "?Listen");
}

void ARobotsGameMode::RestartLevel() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, GetWorld()->GetName());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, GetWorld()->GetMapName());
	EnterLevel(GetWorld()->GetName());
	//GetWorld()->ServerTravel("/Game/maps/" + GetWorld()->GetName()  + "?Listen");

	//GetWorld()->ServerTravel(FString(*GetWorld()->GetName()));
}

void ARobotsGameMode::PlayerDeath() {

	SendServerMessage(FText::FromString("Player Death!"));

	if (restarting) {
		return;
	}


	int32 aliveCount = 0;
	for (TObjectIterator<ARobotCharacter> Itr; Itr; ++Itr)
	{
		// Access the subclass instance with the * or -> operators.
		ARobotCharacter *robot = *Itr;

		if (robot->alive) {
			aliveCount++;
		}
	}
	SendServerMessage(FText::FromString("Remaining Players: " + FString::FromInt(aliveCount)));
	if (aliveCount <= 1) {
		SendServerMessage(FText::FromString("Round Over!"));
		RestartLevel(3);
	}
}

void ARobotsGameMode::SendServerMessage(FText text) {
	ARobotGameState* gs = Cast<ARobotGameState> (GetWorld()->GetGameState());
	gs->SendServerMessage(text);
}
