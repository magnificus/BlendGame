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

void ARobotGameState::addObject(AActor * object)
{
	if (!actorMap.Find(object->GetClass())) {
		TArray<AActor*> newSet;
		newSet.Add(object);
		actorMap.Add(object->GetClass(), newSet);
	} else{
		actorMap.Find(object->GetClass())->Add(object);
	}
}

void ARobotGameState::removeObject(AActor * object)
{
	if(actorMap.Find(object->GetClass()))
		actorMap.Find(object->GetClass())->Remove(object);
}

TArray<AActor*> ARobotGameState::retrieveObjects(UClass* actorClass)
{
	if (actorMap.Find(actorClass))
		return *actorMap.Find(actorClass);
	return TArray<AActor*>();
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
