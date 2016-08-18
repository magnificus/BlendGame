// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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
class ROBOTS_API ACapsule : public AActor
{
	GENERATED_BODY()
	
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
