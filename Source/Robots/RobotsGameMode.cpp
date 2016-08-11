// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Robots.h"
#include "RobotsGameMode.h"
#include "RobotsHUD.h"
#include "RobotCharacter.h"
#include "RobotPlayerState.h"
#include "Engine.h"
#include "ChatWidget.h"
#include "RobotGameState.h"


ARobotsGameMode::ARobotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/robotdude/RobotChar"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ARobotsHUD::StaticClass();
	PlayerStateClass = ARobotPlayerState::StaticClass();

	GameStateClass = ARobotGameState::StaticClass();

	restarting = false;



}
void ARobotsGameMode::RestartLevel(float delay) {
	restarting = true;
	FTimerHandle UnusedHandle;
	SendServerMessage(FText::FromString("Restarting!"));
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ARobotsGameMode::RestartLevel, delay, false);
	restarting = false;
}

void ARobotsGameMode::RestartLevel() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, GetWorld()->GetMapName());
	GetWorld()->ServerTravel("/Game/maps/lab?Listen");
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
	//FSChatMsg newmessage;
	//newmessage.Init(2, FText::FromString("SERVER"), text); // initialize our struct and prep the message

	//APlayerController* MyCon;
	//ARobotsHUD* MyHud;

	//for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	//{
	//	MyCon = Cast<APlayerController>(*Iterator);
	//	if (MyCon)
	//	{
	//		MyHud = Cast<ARobotsHUD>(MyCon->GetHUD());
	//		if (MyHud && MyHud->MyUIWidget.IsValid()) {
	//			MyHud->MyUIWidget->AddMessage(newmessage); // place the chat message on this player controller
	//		}
	//	}
	//}
}