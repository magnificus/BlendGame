// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RobotCharacter.h"
#include "Activatable.generated.h"
/**
 * 
 */
UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UActivatable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IActivatable{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "On Interact")
	virtual void Activate(ARobotCharacter* robot);

	UFUNCTION(BlueprintCallable, Category = "Information")
	virtual FString GetName();

	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Player Health ~ Player Is Healthy Tick"))
	//	void PlayerIsHealthyTick(float CurrentHealth);
};
