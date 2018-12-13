// Fill out your copyright notice in the Description page of Project Settings.

#include "PlannerWorldState.h"

bool FPlannerWorldState::IsPropSatisfied(FWorldProperty test)
{
	FWorldProperty* targetProp = Properties.Find(test);
	if (targetProp && (*targetProp == test))
	{
		return true;
	}
	return false;
}

FWorldProperty::FWorldProperty(EPlannerSymbol key, bool bVal)
{
	this->key = key;
	this->value = bVal;
}
