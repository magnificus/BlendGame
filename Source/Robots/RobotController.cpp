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

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (myJoinWidget)
		{
			//let add it to the view port
			myJoinWidget->AddToViewport();
		}
	}
}

