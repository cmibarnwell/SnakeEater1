// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlanningController.h"

AAIPlanningController::AAIPlanningController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	planComp = CreateDefaultSubobject<UPlannerComponent>("planner");
	//planComp->Activate(); I don't think this is necessary
}

void AAIPlanningController::BeginPlay() 
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI CONTROLLER BEGAN PLAY"));
}