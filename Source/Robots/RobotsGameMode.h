// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameMode.h"
#include "Engine.h"
#include "RobotsGameMode.generated.h"



UCLASS(minimalapi)
class ARobotsGameMode : public AGameMode
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

public:
	ARobotsGameMode();

	UFUNCTION()
		virtual void K2_PostLogin();
	bool restarting;

	void RestartLevel(float delay);
	void RestartLevel();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void EnterLevel(FString name);

	void PlayerDeath();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SendServerMessage(FText message);

};



