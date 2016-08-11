// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "RobotGameState.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTS_API ARobotGameState : public AGameState
{
	GENERATED_BODY()


public:

	ARobotGameState();

	
	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
		virtual void SendServerMessage(const FText& text);

	virtual void SendServerMessage_Implementation(const FText& text);
	virtual bool SendServerMessage_Validate(const FText& text);
	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
		virtual void SendServerMessageMulti(const FText& text);

	virtual void SendServerMessageMulti_Implementation(const FText& text);
	virtual bool SendServerMessageMulti_Validate(const FText& text);
	
};
