// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "Capsule.h"


// Sets default values
ACapsule::ACapsule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACapsule::BeginPlay()
{
	AActor::BeginPlay();
	
}

// Called every frame
void ACapsule::Tick( float DeltaTime )
{
	AActor::Tick( DeltaTime );

}

EPowerUp ACapsule::GetPowerUp() {
	return EPowerUp(FMath::Rand() % EPowerUp_Count);

}

FString ACapsule::GetName()
{
	return "Loot Crate";
}

void ACapsule::Activate(ARobotCharacter* robot) {
	EPowerUp e = GetPowerUp();
	if (e == EPowerUp::P_LASER) {
		robot->SetCanLaser(true);
	}
	else if (e == EPowerUp::P_ASSIMILATE) {
		robot->SetCanAssimilate(true);
	}
	else if (e == EPowerUp::P_REVEAL) {
		robot->SetCanReveal(true);
	}
	else if (e == EPowerUp::P_BOMB) {
		robot->SetCanBomb(true);
	}
	Destroy();

}

