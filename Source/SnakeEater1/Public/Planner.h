// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPAction.h"
#include "PlannerNode.h"
#include "Planner.generated.h"


typedef uint32 ActionID;
/**
 * 
 */
UCLASS()
class SNAKEEATER1_API UPlanner : public UObject
{
	GENERATED_BODY()

		uint32 numActions;
public:

	FPlannerNode* SearchResultOnSuccess;
	
	UPROPERTY()
	TArray<UGOAPAction*> ActionTable;

	UPROPERTY()
	TMap<EPlannerSymbol, uint32> EffectActionMap; //Assume one action per effect now but will need to expand this

	void AddAction(UGOAPAction *action);
	bool SearchForGoal(FPlannerWorldState GoalConditions);
};


