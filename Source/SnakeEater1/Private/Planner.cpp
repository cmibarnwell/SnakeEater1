// Fill out your copyright notice in the Description page of Project Settings.

#include "Planner.h"

UPlanner::UPlanner()
{

}

UPlanner::~UPlanner()
{
}

void UPlanner::AddAction(UGOAPAction action)
{
}

TSharedPtr<FPlannerNode> UPlanner::MakePlan(FPlannerWorldState GoalConditions)
{
	//goal state and targetstate are expressed in terms of the same properties...
	FPlannerNode CurrentNode;
	CurrentNode.Unsatisfied = GoalConditions;
	CurrentNode.costOfAction = 0;

	TArray<FPlannerNode> Fringe;
	TSet<FPlannerNode, NodeKeyFuncs> ClosedSet;
	Fringe.Push(CurrentNode);
	Fringe.Heapify();


	//A* search from goal state
	//closed set (action)
	//fringe (Planner Nodes)
	/*while (current is not target and fringe is not empty){
		current = fringe pop
		fringe push (N, cost(N)) for Node N in succ(current)

		successor(parent) : Node n foreach n not in Closed iff exists edge(parent, n)
		exists edge(n0, n1) iff exists (k->v) in n1.effects s.t (e == pre), (k->e) in n1, (k->pre) in n0
	}
	return current
	*/
	while (!CurrentNode.HasReachedTarget() && (Fringe.Num() > 0))
	{
		Fringe.HeapPop(CurrentNode);
		TSet< FPlannerNode, NodeKeyFuncs > children;
		for (auto& Precond : CurrentNode.Unsatisfied.Properties)
		{
			//find actions that MIGHT satisfy effects (will change to TMultiMap so multiple actions can have same effect)
			ActionID* PotentialAction = EffectActionMap.Find(Precond.key);
			
			if (PotentialAction)
			{
				UGOAPAction* action = ActionTable[*PotentialAction];
				if( (Precond == *(action->Effects.Find(Precond.key))) && action->IsContextSatisfied())
				{
					//check to see if we already a made a child node for this action
					TSharedPtr<FPlannerNode> newChild(new FPlannerNode());
					newChild->action = *PotentialAction;
					FPlannerNode* child = children.Find(*newChild);
					if (child)
					{
						child->Unsatisfied.Properties.Remove(Precond);
					}
					else 
					{
						newChild->costOfAction = action->cost;
						newChild->ParentNode = TSharedPtr<FPlannerNode>(&CurrentNode);
						children.Add(*newChild);
					}
				}
			}
		}
		for (auto& successor : children) 
		{
			Fringe.HeapPush(successor);
		}
	}
	return TSharedPtr<FPlannerNode>(&CurrentNode);
}