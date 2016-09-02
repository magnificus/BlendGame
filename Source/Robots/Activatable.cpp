// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "Activatable.h"

UActivatable::UActivatable(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP) {

}
// Give GetHealth a default implementation
float IActivatable::GetHealth() {
	return 0.0f;
}
