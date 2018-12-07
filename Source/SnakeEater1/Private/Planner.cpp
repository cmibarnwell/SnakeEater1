// Fill out your copyright notice in the Description page of Project Settings.

#include "Planner.h"

void UPlanner::AddAction(UGOAPAction *action)
{
	ActionTable.Add(action);
	for (auto& e : action->Effects)
	{
		EffectActionMap.Add(e.Key, numActions);
	}
	numActions++;
}

bool UPlanner::SearchForGoal(FPlannerWorldState GoalConditions)
{
	UE_LOG(LogTemp, Warning, TEXT("NumActions:%d"), ActionTable.Num())
	for (auto& p : GoalConditions.Properties)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d | %d"), static_cast<uint32>(p.key), p.value)
	}
	
	//goal state and targetstate are expressed in terms of the same properties...
	FPlannerNode *CurrentNode = new FPlannerNode();
	CurrentNode->Unsatisfied = GoalConditions;
	CurrentNode->cost = 0;
	CurrentNode->action = numActions;
	CurrentNode->isTerminalNode = true;
	TArray<FPlannerNode> Fringe;
	TSet<uint32> ClosedSet;
	Fringe.Heapify();
	bool isFringeEmpty = false;

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
	while (!isFringeEmpty)
	{
		if (CurrentNode->HasReachedTarget()) {
			//TODO: cache result
			SearchResultOnSuccess = CurrentNode;
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("Current Num: %d"), Fringe.Num())
		ClosedSet.Add(CurrentNode->action);

		
		TSet< FPlannerNode, NodeKeyFuncs > children;
		for (auto& Precond : CurrentNode->Unsatisfied.Properties)
		{

			//find actions that MIGHT satisfy effects (will change to TMultiMap so multiple actions can have same effect)
			ActionID* PotentialAction = EffectActionMap.Find(Precond.key);
			if (PotentialAction != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Looking at action %d"), *PotentialAction)
				UGOAPAction* action = ActionTable[*PotentialAction];
				FWorldProperty* p = action->Effects.Find(Precond.key);
				if (p) {
					UE_LOG(LogTemp, Error, TEXT("Action prop: %d | %d"), static_cast<uint32>(p->key), p->value)
					UE_LOG(LogTemp, Error, TEXT("Precondition: %d | %d"), static_cast<uint32>(Precond.key), Precond.value)
					
					if (Precond == *p && action->IsContextSatisfied())
					{
						//check to see if we already a made a child node for this action
						FPlannerNode* newChild = new FPlannerNode();
						newChild->action = *PotentialAction;
						
						if (!ClosedSet.Contains(*PotentialAction)) 
						{
							newChild->ParentNode = CurrentNode;
							newChild->cost = action->cost + CurrentNode->cost;
							for (auto & pre : action->Preconditions)
							{
								newChild->Unsatisfied.Properties.Add(pre.Value);
								newChild->cost++;
							}
							Fringe.HeapPush(*newChild);
						}
					}
				}
			}
		}
		isFringeEmpty = (Fringe.Num() == 0);
		if (!isFringeEmpty)
		{
			Fringe.HeapPop(*CurrentNode);
		}
	}

	SearchResultOnSuccess = nullptr;
	return false;
}