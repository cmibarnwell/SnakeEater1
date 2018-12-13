// Fill out your copyright notice in the Description page of Project Settings.

#include "PlannerComponent.h"

// Sets default values for this component's properties
UPlannerComponent::UPlannerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlannerComponent::BeginPlay()
{
	Super::BeginPlay();

}

//make actions in Pawn and add them to Planner
void UPlannerComponent::AddAction(UGOAPAction *action)
{
	ActionTable.Add(action);
	for (auto& e : action->Effects)
	{
		EffectActionMap.Add(e.Key, numActions);
	}
	numActions++;
}

bool UPlannerComponent::SearchForGoal(FPlannerWorldState GoalConditions)
{
	SearchResultOnSuccess = nullptr;
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
	CurrentNode->ParentNode = nullptr;
	TArray<FPlannerNode*> Fringe;
	TSet<uint32> ClosedSet;
	Fringe.HeapSort([](FPlannerNode &A, FPlannerNode &B) { return (A.cost + A.heuristic) < (B.cost + B.heuristic); });
	bool isFringeEmpty = false;
	

	//A* search from goal state
	//closed set (action)
	//fringe (Planner Nodes)
	/*while (current is not target and fringe is not empty){
		current = fringe pop
		add current to Closed

		fringe push (N, cost(N)) for Node N in succ(current)
			successor(parent) : Node n foreach n not in Closed iff exists edge(parent, n)
			exists edge(n0, n1) iff exists (k->v) in n1.effects s.t (e == pre), (k->e) in n1, (k->pre) in n0
	}
	return current
	*/
	do //I didn't want to create a dummy node since it made some weird behavior
	{
		ClosedSet.Add(CurrentNode->action);

		if (HaveReachedTarget(CurrentNode)) 
		{
			//TODO: cache result
			UE_LOG(LogTemp, Warning, TEXT("SEARCH RESULT SUCCEEDED"))
			SearchResultOnSuccess = CurrentNode;
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("Current Num: %d"), Fringe.Num())

		//TODO: add a check somewhere
		//to see if the precondition is satisfied by the world state
		//before adding to unsatisfied properties

		//add preconditions to unsatisfied properties
		for (auto& Precond : CurrentNode->Unsatisfied.Properties) // should probably put world state check here actually
		{

			//find actions that MIGHT satisfy effects (will change to TMultiMap so multiple actions can have same effect)
			ActionID* PotentialAction = EffectActionMap.Find(Precond.key);
			if (PotentialAction != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Looking at action %d"), *PotentialAction)
				UGOAPAction* action = ActionTable[*PotentialAction];
				FWorldProperty* p = action->Effects.Find(Precond.key);
				if (p) 
				{
					UE_LOG(LogTemp, Error, TEXT("Action prop: %d | %d"), static_cast<uint32>(p->key), p->value);
					UE_LOG(LogTemp, Error, TEXT("Precondition: %d | %d"), static_cast<uint32>(Precond.key), Precond.value);
					
					if (!ClosedSet.Contains(*PotentialAction))
					{
						if (Precond == *p)
						{
							//check to see if we already CHECKED a child node for this action
							FPlannerNode* newChild = new FPlannerNode();
							newChild->action = *PotentialAction;

							newChild->isTerminalNode = false;
							newChild->ParentNode = ((CurrentNode->isTerminalNode) ? nullptr : CurrentNode);
							newChild->cost = action->cost + CurrentNode->cost;
							for (auto & pre : action->Preconditions)
							{
								newChild->Unsatisfied.Properties.Add(pre.Value);
							}
							newChild->CalculateHeuristic();
							Fringe.HeapPush(newChild, [](FPlannerNode &A, FPlannerNode &B) { 
								return (A.cost + A.heuristic) < (B.cost + B.heuristic); });
						}
					}
				}
			}
		}

		isFringeEmpty = (Fringe.Num() == 0);
		//pop from fringe afterwards rather than create a dummy node at the start
		if (!isFringeEmpty)
		{
			Fringe.HeapPop(CurrentNode, [](FPlannerNode &A, FPlannerNode &B) {
				return (A.cost + A.heuristic) < (B.cost + B.heuristic); 
			});
		}
	} while (!isFringeEmpty);

	UE_LOG(LogTemp, Warning, TEXT("Search Result Failed"));
	SearchResultOnSuccess = nullptr;
	return false;
}

UGOAPAction* UPlannerComponent::GetTopAction()
{
	if (SearchResultOnSuccess)
	{
		UGOAPAction* act = ActionTable[SearchResultOnSuccess->action];
		SearchResultOnSuccess = SearchResultOnSuccess->ParentNode;
		return act;
	}
	UE_LOG(LogTemp, Error, TEXT("NO PARENT NODE"))
	return nullptr;
}

bool UPlannerComponent::HaveReachedTarget(FPlannerNode* CurrentNode)
{
	if (!CurrentNode->isTerminalNode)
	{
		UGOAPAction* action = ActionTable[CurrentNode->action];
		return CurrentNode->HasReachedTarget() && action->IsValidAction(GetController());
	}
	return false;
}