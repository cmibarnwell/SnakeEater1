// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIController.h"
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
	bool isActivated;
	UPROPERTY()
	uint32 cost; //assigned
	//should make protected

	virtual void Activate(AAIController*);
	virtual void Deactivate(AAIController*);

	//Can probably change this to TSet
	//also make protected
	TMap<EPlannerSymbol, FWorldProperty> Preconditions;
	TMap<EPlannerSymbol, FWorldProperty> Effects;

	bool DoesSatisfyProperty(EPlannerSymbol Key, FWorldProperty TargetProperty);
	virtual bool IsContextSatisfied() { return true; } //Will interact with controller here, don't worry for now
	virtual bool IsValidAction(AAIController* controller) { return true; }
};