// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "PlannerComponent.h"
#include "ActionComponent.h"
#include "AIPlanningController.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEEATER1_API AAIPlanningController : public AAIController
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY()
	UPlannerComponent* planComp;
	bool NeedNewPlan;
	bool isPlanning;
	UGOAPAction* currentAction;
	TArray<FPlannerWorldState> Goals;
	//TODO: turn this into array
	FPlannerWorldState goal;
public:
	UPlannerComponent * GetPlannerComponent() { return planComp; }

	UFUNCTION(BlueprintCallable)
	void SetReplan(bool ShouldReplan) { NeedNewPlan = ShouldReplan; }

	void BeginPlay() override;
	void Tick(float deltatime) override;

	void ReevaluateGoals();
};
