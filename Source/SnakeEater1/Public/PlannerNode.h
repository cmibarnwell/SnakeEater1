#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Set.h"
#include "PlannerWorldState.h"

#include "PlannerNode.generated.h"

USTRUCT()
struct FPlannerNode
{
	GENERATED_BODY()

	FPlannerNode* ParentNode;

	uint32 cost;

	bool isTerminalNode;
	
	typedef uint32 ActionID;
	ActionID action;

	UPROPERTY()
	FPlannerWorldState Unsatisfied;

	uint32 heuristic()
	{
		return Unsatisfied.Properties.Num();
	}

	friend bool operator<(const FPlannerNode &lhs, const FPlannerNode &rhs)
	{
		return lhs.cost < rhs.cost;
	}

	
	bool HasReachedTarget() { return Unsatisfied.Properties.Num() == 0; }

	
};


//Custom keyfunctions to use FPlannerNode in TSet
//Compares nodes by actionID and ignores unsatisfied conditions
//keyhash is just action ID since we used a fixed size table
struct NodeKeyFuncs : DefaultKeyFuncs<FPlannerNode> {
	typedef typename TCallTraits<FPlannerNode>::ParamType KeyInitType;
	typedef typename TCallTraits<FPlannerNode>::ParamType ElementInitType;

	static KeyInitType GetSetKey(ElementInitType node) { return node; }
	static uint32 GetKeyHash(KeyInitType node) { return node.action ; }
	static bool Matches(KeyInitType A, KeyInitType B) { return A.action == B.action; }
};