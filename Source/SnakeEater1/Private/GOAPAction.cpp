// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPAction.h"

void UGOAPAction::Activate(AAIController* controller)
{
	isActivated = true;
	isFinished = false;
}

void UGOAPAction::Deactivate(AAIController* controller)
{
	isFinished = true;
}

void UGOAPAction::SetPrec(FWorldProperty Prop)
{
	Preconditions.Add(Prop.key, Prop);
}

void UGOAPAction::SetEffect(FWorldProperty Prop)
{
	Effects.Add(Prop.key, Prop);
}

bool UGOAPAction::DoesSatisfyProperty(FWorldProperty TestProperty)
{
	FWorldProperty* TargetProperty = Effects.Find(TestProperty.key);

	if (TargetProperty && (TestProperty == *TargetProperty) )
	{
		return true;
	}
	return false;
}
