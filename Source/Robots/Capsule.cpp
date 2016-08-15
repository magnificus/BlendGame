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
	Super::BeginPlay();
	
}

// Called every frame
void ACapsule::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

EPowerUp ACapsule::GetPowerUp() {
	return EPowerUp(FMath::Rand() % EPowerUp_Count);

}

