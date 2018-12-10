// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "PlannerWorldState.h"
#include "TestActionCover.generated.h"

UCLASS()
class SNAKEEATER1_API UTestActionIdle : public UGOAPAction
{
	GENERATED_BODY()

public:
	UTestActionIdle();
	
	void ExecuteAction() override;
};
