// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlanningController.h"

AAIPlanningController::AAIPlanningController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	planComp = CreateDefaultSubobject<UPlannerComponent>("planner");
	//planComp->Activate(); I don't think this is necessary
	NeedToReplan = false; //this will be false for now. Will eventually be true by default
	goal.Properties.Add(FWorldProperty(EPlannerSymbol::k_TargetIsDead, true));
	planComp->AddAction(NewObject<UAIAttack>());
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
		//reevaluate goals
		//check goals by priority
		//attempt to make plan
	if (planComp->SearchResultOnSuccess)
	{
		NeedToReplan = false;
		if (planComp->GetNextAction()->isActivated == false)
		{
			planComp->GetNextAction()->Activate(this);
		}
	}
	else
	{
		if (NeedToReplan) 
		{
			bool success = planComp->SearchForGoal(goal); //will use flag when we make into a loop
		}
	}
}
