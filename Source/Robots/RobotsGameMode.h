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

	void PlayerDeath();
	void SendServerMessage(FText message);



	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<class UUserWidget> playerHUDClass;

	//class UUSerWidget* widgetInstance;
};



