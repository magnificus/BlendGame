// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "Activatable.h"

UActivatable::UActivatable(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}
// Give GetHealth a default implementation
FString IActivatable::GetName() {
	return "Bazinga you fucking nerd";
}

void IActivatable::Activate(ARobotCharacter* robot) {
}