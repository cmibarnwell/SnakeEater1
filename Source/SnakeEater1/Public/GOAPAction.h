// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlannerWorldState.h"
#include "GOAPAction.generated.h"



/**
 * 
 */
UCLASS()
class SNAKEEATER1_API UGOAPAction : public UObject
{
	GENERATED_BODY()	
public:
	UPROPERTY()
	uint32 cost; //assigned


	//Can probably change this to TSet
	TMap<EPlannerSymbol, FWorldProperty> Preconditions;
	TMap<EPlannerSymbol, FWorldProperty> Effects;

	bool DoesSatisfyProperty(EPlannerSymbol Key, FWorldProperty TargetProperty);
	virtual bool IsContextSatisfied() { return true; } //Will interact with controller here, don't worry for now
};