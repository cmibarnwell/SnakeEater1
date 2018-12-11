// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlanningController.h"

AAIPlanningController::AAIPlanningController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	planComp = CreateDefaultSubobject<UPlannerComponent>("planner");
	planComp->Activate();// I don't think this is necessary
	NeedNewPlan = false; //this will be false for now. Will eventually be true by default
	goal.SetProp( FWorldProperty(EPlannerSymbol::k_TargetIsDead, true));
	Goals.Add(goal);
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
	if (NeedNewPlan && !isPlanning)
	{
		currentAction = nullptr;
		isPlanning = true;
		//make sure there are no race conditions
		ReevaluateGoals();
		for (auto & goal : Goals)
		{
			bool success = planComp->SearchForGoal(goal);
			if (success)
			{
				NeedNewPlan = false;
				break;
			}
		}
		isPlanning = false;
	} 
	else if (!NeedNewPlan)
	{
		if (!currentAction) // TODO: and action is complete!
		{
			currentAction = planComp->GetNextAction();
		}
		if (currentAction && !(currentAction->isActivated))
		{
			currentAction->Activate(this);
		}
	}
	
}

void AAIPlanningController::ReevaluateGoals()
{

}