// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlannerComponent.h"
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

public:

	void BeginPlay() override;
};
