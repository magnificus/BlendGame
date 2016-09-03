// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "PhysicsMPBase.h"
#include "BarrelActor.generated.h"

UCLASS()
class ROBOTS_API ABarrelActor : public APhysicsMPBase, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrelActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "On Interact")
		virtual FString GetName() override;
	UFUNCTION(BlueprintCallable, Category = "Information")
		virtual void Activate(ARobotCharacter* robot) override;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "User activated")
		void UserActivated(ARobotCharacter* robot);
	
};
