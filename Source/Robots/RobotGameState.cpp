// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "RobotGameState.h"
#include "RobotsHud.h"
#include "ChatWidget.h"
#include "Engine.h"

ARobotGameState::ARobotGameState()
{

}


bool ARobotGameState::SendServerMessageMulti_Validate(const FText& text) {
	return true;
}

void ARobotGameState::SendServerMessageMulti_Implementation(const FText& text) {
	FSChatMsg newmessage;
	newmessage.Init(2, FText::FromString("SERVER"), text); // initialize our struct and prep the message

	APlayerController* MyCon;
	ARobotsHUD* MyHud;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		MyCon = Cast<APlayerController>(*Iterator);
		if (MyCon)
		{
			MyHud = Cast<ARobotsHUD>(MyCon->GetHUD());
			if (MyHud && MyHud->MyUIWidget.IsValid()) {
				MyHud->MyUIWidget->AddMessage(newmessage); // place the chat message on this player controller
			}
		}
	}
}

bool ARobotGameState::SendServerMessage_Validate(const FText& text) {
	return true;
}

void ARobotGameState::SendServerMessage_Implementation(const FText& text) {
	SendServerMessageMulti(text);
}
