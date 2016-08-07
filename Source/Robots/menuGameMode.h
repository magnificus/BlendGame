// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
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
	void HostGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ExecuteFunction(FString parameter);
	
	
	
};
