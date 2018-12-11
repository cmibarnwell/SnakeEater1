// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GOAPAction.h"
#include "PlannerNode.h"
#include "TestActionCover.h"

#include "PlannerComponent.generated.h"


typedef uint32 ActionID;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNAKEEATER1_API UPlannerComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

private:
	TArray<FPlannerWorldState> Goals; //should be call to controlled pawn

	UPROPERTY()
	TArray<UGOAPAction*> ActionTable;

	UPROPERTY()
	TMap<EPlannerSymbol, uint32> EffectActionMap; //Assume one action per effect now but will need to expand this

	bool needsPlan;

	FPlannerNode* Plan; //maybe change to sharedptr

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	uint32 numActions;

	FPlannerNode * SearchResultOnSuccess; //redundant

	void AddAction(UGOAPAction *action);
	bool SearchForGoal(FPlannerWorldState GoalConditions);
	bool HasPlan() { return Plan ? true : false; }
	UGOAPAction* GetNextAction();
	AAIController* GetController() { return Cast<AAIController>(GetOwner()); }
};
