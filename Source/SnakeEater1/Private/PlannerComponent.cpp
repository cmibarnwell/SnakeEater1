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

FPlannerNode* UPlannerComponent::CreateNode(FPlannerNode* CurrentNode, TArray<FWorldProperty> &CurrentWorldState, uint32 ActionID)
{
	UGOAPAction* Action = ActionTable[ActionID];

	FPlannerNode* newChild = new FPlannerNode();
	newChild->action = ActionID;

	newChild->isTerminalNode = false;
	newChild->ParentNode = ((CurrentNode->isTerminalNode) ? nullptr : CurrentNode);
	newChild->cost = Action->cost + CurrentNode->cost;

	//merge the world states
	for (auto& Property : CurrentNode->Unsatisfied.Properties)
	{
		//add every property not satisified by the action's effects to the newchild state
		if (!Action->DoesSatisfyProperty(Property) && !(Property == CurrentWorldState[(uint32)Property.key]))
		{
			newChild->Unsatisfied.SetProp(Property);
		}
	}

	//this is why we should use a set 
	for (auto & pre : Action->Preconditions)
	{
		//add all action preconditions
		newChild->Unsatisfied.Properties.Add(pre.Value);
	}

	//calculate remainind unsatisfied properties
	newChild->CalculateHeuristic();
	return newChild;
}

//check validation conditions
bool UPlannerComponent::HaveReachedTarget(FPlannerNode* CurrentNode)
{
	if (!CurrentNode->isTerminalNode)
	{
		UGOAPAction* action = ActionTable[CurrentNode->action];
		return CurrentNode->HasReachedTarget() && action->IsValidAction(GetController());
	}
	return false;
}

bool UPlannerComponent::SearchForGoal(FPlannerWorldState GoalConditions, TArray<FWorldProperty> &CurrentWorldState)
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
	do //I didn't want to add a dummy node to the fringe since it did weird stuff
	{
		ClosedSet.Add(CurrentNode->action); //this is fine though

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
		for (auto& Precond : CurrentNode->Unsatisfied.Properties)
		{
			if (!(Precond == CurrentWorldState[(uint32)Precond.key]))
			{
				TArray<ActionID> Actions;
				//find actions that MIGHT satisfy effects (will change to TMultiMap so multiple actions can have same effect)
				EffectActionMap.MultiFind(Precond.key, Actions);
				for (auto& actionIndex : Actions)
				{
					if (!ClosedSet.Contains(actionIndex))
					{
						UE_LOG(LogTemp, Error, TEXT("Looking at action %d"), actionIndex)

						FPlannerNode* newChild = CreateNode(CurrentNode, CurrentWorldState, actionIndex);
						Fringe.HeapPush(newChild, [](FPlannerNode &A, FPlannerNode &B) {
							return (A.cost + A.heuristic) < (B.cost + B.heuristic); });
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

