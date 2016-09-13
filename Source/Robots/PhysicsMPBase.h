// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PhysicsMPBase.generated.h"

UCLASS()
class ROBOTS_API APhysicsMPBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APhysicsMPBase();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Mesh", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mesh;

	UFUNCTION()
		void OnRep_currTrans();

	UPROPERTY(ReplicatedUsing=OnRep_currTrans)
		FTransform currTrans;
	UPROPERTY(Replicated)
		FVector currVel;
	UPROPERTY(Replicated)
		FVector currAngVel;

	FTransform lastTrans;

};
