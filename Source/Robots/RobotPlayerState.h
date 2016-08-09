// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"

#include "RobotsHUD.h"

#include "RobotPlayerState.generated.h"

/**
*
*/
UCLASS()
class ROBOTS_API ARobotPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ARobotPlayerState();

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
		virtual void UserChatRPC(const FSChatMsg& newmessage); // first rpc for the server
	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
		virtual void UserChat(const FSChatMsg& newmessage); // second rpc for all the clients
};