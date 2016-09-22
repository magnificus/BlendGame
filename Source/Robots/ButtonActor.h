// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Activatable.h"
#include "GameFramework/Actor.h"
#include "ButtonActor.generated.h"

UCLASS()
class ROBOTS_API AButtonActor : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "User activated")
		void UserActivated(ARobotCharacter* robot);

	UFUNCTION(BlueprintCallable, Category = "On Interact")
		virtual FString GetName() override;
	UFUNCTION(BlueprintCallable, Category = "Information")
		virtual void Activate(ARobotCharacter* robot) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Information")
		FString name;
	
	
};
