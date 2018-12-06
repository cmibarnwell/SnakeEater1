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
	
public:
	
	TArray<UGOAPAction*> ActionTable;
	TMap<EPlannerSymbol, ActionID> EffectActionMap; //Assume one action per effect now but will need to expand this

	UPlanner();
	~UPlanner();

	void AddAction(UGOAPAction action);
	TSharedPtr<FPlannerNode> MakePlan(FPlannerWorldState GoalConditions);
};


