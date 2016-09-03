// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "RobotCharacter.h"
#include "Capsule.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPowerUp : uint8
{
	P_LASER 	UMETA(DisplayName = "Laser"),
	P_ASSIMILATE 	UMETA(DisplayName = "Assimilate"),
	P_REVEAL	UMETA(DisplayName = "Reveal"),
	P_BOMB	UMETA(DisplayName = "Bomb")
};

const int32 EPowerUp_Count = 4;

UCLASS()
class ACapsule : public AActor, public IActivatable
{
	GENERATED_BODY()

	//void Activate(ARobotCharacter* robot);
	UFUNCTION(BlueprintCallable, Category = "On Interact")
	virtual FString GetName() override;
	UFUNCTION(BlueprintCallable, Category = "Information")
	virtual void Activate(ARobotCharacter* robot) override;

public:	
	// Sets default values for this actor's properties
	ACapsule();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		EPowerUp GetPowerUp();

	
};
