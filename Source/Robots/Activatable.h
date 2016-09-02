// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Activatable.generated.h"
/**
 * 
 */
UINTERFACE(MinimalAPI)
class UActivatable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IActivatable{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "On Interact"))
	void OnInteract(const TScriptInterface<IActivatable> &clicked);
	virtual float GetHealth();

};
