// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "BarrelActor.h"


// Sets default values
ABarrelActor::ABarrelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABarrelActor::BeginPlay()
{
	APhysicsMPBase::BeginPlay();
	
}

// Called every frame
void ABarrelActor::Tick( float DeltaTime )
{
	APhysicsMPBase::Tick( DeltaTime );

}

FString ABarrelActor::GetName()
{
	return "Barrel";
}

void ABarrelActor::Activate(ARobotCharacter * robot)
{
	UserActivated(robot);
}



