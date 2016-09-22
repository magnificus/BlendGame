// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "ButtonActor.h"


// Sets default values
AButtonActor::AButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	name = "Button";
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FString AButtonActor::GetName()
{
	return name;
}

void AButtonActor::Activate(ARobotCharacter * robot)
{
	UserActivated(robot);
}

