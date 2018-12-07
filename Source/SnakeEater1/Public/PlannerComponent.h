// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Planner.h"
#include "Components/ActorComponent.h"
#include "TestActionCover.h"
#include "PlannerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNAKEEATER1_API UPlannerComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY()
	UPlanner* Planner;
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

	
};
