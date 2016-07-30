// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "RobotsHUD.generated.h"

UCLASS()
class ARobotsHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARobotsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */

};

