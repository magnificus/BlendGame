// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "RobotsGameMode.generated.h"

UCLASS(minimalapi)
class ARobotsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ARobotsGameMode();

	UFUNCTION()
		void K2_PostLogin();



	bool restarting;

	void RestartLevel(float delay);
	void RestartLevel();


	void PlayerDeath();

	void SendServerMessage(FText message);

};



