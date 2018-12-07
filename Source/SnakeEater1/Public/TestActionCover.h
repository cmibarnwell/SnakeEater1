// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "PlannerWorldState.h"
#include "TestActionCover.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEEATER1_API UTestActionCover : public UGOAPAction
{
	GENERATED_BODY()
	
public:
	UTestActionCover();

	void ExecuteAction();
};

UCLASS()
class SNAKEEATER1_API UTestActionChain : public UGOAPAction
{
	GENERATED_BODY()

public:
	UTestActionChain();

	void ExecuteAction();
};
