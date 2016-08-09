// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "SlateCore.h"
#include "Engine.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "RobotController.h"





void ARobotController::showJoinWidget() {
	if (joinWidget) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		myJoinWidget = CreateWidget<UUserWidget>(this, joinWidget);

		if (myJoinWidget)
		{
			myJoinWidget->AddToViewport();
		}
	}
}

