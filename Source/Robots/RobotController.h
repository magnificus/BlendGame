// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RobotController.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTS_API ARobotController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> joinWidget;

	// Variable to hold the widget After Creating it.
	UUserWidget* myJoinWidget;

	void showJoinWidget();

	
	
};
