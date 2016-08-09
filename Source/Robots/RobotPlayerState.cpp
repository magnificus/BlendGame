// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "RobotPlayerState.h"

#include "RobotsHUD.h"
#include "ChatWidget.h"

ARobotPlayerState::ARobotPlayerState()
{

}

bool ARobotPlayerState::UserChatRPC_Validate(const FSChatMsg& newmessage)
{
	return true;
}
void ARobotPlayerState::UserChatRPC_Implementation(const FSChatMsg& newmessage)
{
	UserChat(newmessage);
}
bool ARobotPlayerState::UserChat_Validate(const FSChatMsg& newmessage)
{
	return true;
}
void ARobotPlayerState::UserChat_Implementation(const FSChatMsg& newmessage)
{
	APlayerController* MyCon;
	ARobotsHUD* MyHud;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		MyCon = Cast<APlayerController>(*Iterator);
		if (MyCon)
		{
			MyHud = Cast<ARobotsHUD>(MyCon->GetHUD());
			if (MyHud && MyHud->MyUIWidget.IsValid())
				MyHud->MyUIWidget->AddMessage(newmessage); // place the chat message on this player controller
		}
	}
}