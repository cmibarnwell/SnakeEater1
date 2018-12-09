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

	bool needsPlan;

	UPROPERTY()
	UGOAPAction* currentAction;

	FPlannerNode* Plan;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	uint32 numActions;

	FPlannerNode * SearchResultOnSuccess;

	UPROPERTY()
		TArray<UGOAPAction*> ActionTable;

	UPROPERTY()
		TMap<EPlannerSymbol, uint32> EffectActionMap; //Assume one action per effect now but will need to expand this

	void AddAction(UGOAPAction *action);
	bool SearchForGoal(FPlannerWorldState GoalConditions);
	

};
