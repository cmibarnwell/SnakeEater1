// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "PlannerComponent.h"
#include "ConstructorHelpers.h"
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
	bool PawnHasAmmo;
	UPROPERTY()
	UGOAPAction* currentAction;
	TArray<FPlannerWorldState> Goals;
	TArray<FWorldProperty> CurrentWorldState;
public:
	UPlannerComponent * GetPlannerComponent() { return planComp; }

	UFUNCTION(BlueprintCallable)
	void SetReplan(bool ShouldReplan) { NeedNewPlan = ShouldReplan; }

	UFUNCTION(BlueprintCallable)
	void OnActionComplete();
	void BeginPlay() override;
	void Tick(float deltatime) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(const FName& KeyName, AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void TrackTarget(bool Track);

	UFUNCTION(BlueprintCallable)
		void SetActionComplete(bool IsActionComplete);

	void ReevaluateGoals();
};
