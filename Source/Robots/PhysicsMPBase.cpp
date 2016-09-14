// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "PhysicsMPBase.h"
#include "UnrealNetwork.h"



// Sets default values
APhysicsMPBase::APhysicsMPBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	mesh->SetupAttachment(RootComponent);
	mesh->SetSimulatePhysics(true);

	bReplicates = true;
	bReplicateMovement = true;
	replicatePos = true;
}

// Called when the game starts or when spawned
void APhysicsMPBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsMPBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (replicatePos && Role == ROLE_Authority) {
		if (!mesh->GetComponentTransform().Equals(lastTrans, 0.1f)) {
			currTrans = mesh->GetComponentTransform();
		}
		currVel = mesh->GetPhysicsLinearVelocity();
		currAngVel = mesh->GetPhysicsAngularVelocity();
		lastTrans = mesh->GetComponentTransform();
	}

}

void APhysicsMPBase::OnRep_currTrans() {
	if (replicatePos) {
		mesh->SetPhysicsLinearVelocity(currVel);
		mesh->SetPhysicsAngularVelocity(currAngVel);
		mesh->SetWorldTransform(currTrans);
	}

}

void APhysicsMPBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APhysicsMPBase, currTrans);
	DOREPLIFETIME(APhysicsMPBase, currVel);
	DOREPLIFETIME(APhysicsMPBase, currAngVel);
	DOREPLIFETIME(APhysicsMPBase, replicatePos);

}