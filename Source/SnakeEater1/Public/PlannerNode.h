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

	TSharedPtr<FPlannerNode> ParentNode;
	uint32 costOfAction;
	typedef uint32 ActionID;
	ActionID action;
	FPlannerWorldState Unsatisfied;

	friend bool operator<(const FPlannerNode &lhs, const FPlannerNode &rhs)
	{
		return lhs.costOfAction + lhs.Unsatisfied.Properties.Num() < rhs.costOfAction + rhs.Unsatisfied.Properties.Num();
	}

	bool HasReachedTarget() { return Unsatisfied.Properties.Num() == 0; }

	
};

struct NodeKeyFuncs : DefaultKeyFuncs<typename FPlannerNode, false> {
	static FPlannerNode GetSetKey(FPlannerNode node) { return node; }
	static uint32 GetKeyHash(FPlannerNode node) { return node.action; }
	static bool Matches(FPlannerNode n0, FPlannerNode n1) { return n0.action == n1.action; }
};