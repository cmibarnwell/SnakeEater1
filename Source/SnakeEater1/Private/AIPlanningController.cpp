// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlanningController.h"

AAIPlanningController::AAIPlanningController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	planComp = CreateDefaultSubobject<UPlannerComponent>("planner");
	//planComp->Activate(); I don't think this is necessary
	NeedToReplan = true;
}

void AAIPlanningController::BeginPlay() 
{
	Super::BeginPlay();
}

void AAIPlanningController::Tick(float deltatime)
{
	Super::Tick(deltatime);

	//if we have a plan
		//if our top action is not activated, activate it
		//if its complete, get the next action
		//if it failed, flag REPLAN
	//if flagged REPLAN
		//go through possessed pawn's goals by priority
		//attempt to make plan
	if (planComp->HasPlan())
	{
		NeedToReplan = false;

	}
	else
	{

	}
}
