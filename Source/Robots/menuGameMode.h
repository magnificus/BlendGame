// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "RobotController.h"
#include "menuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTS_API AmenuGameMode : public AGameMode
{
	GENERATED_BODY()


public:
	AmenuGameMode();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ExecuteFunction(FString parameter);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void HostGame(FString name);
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void JoinGame(FString address);
	
	
	
};
