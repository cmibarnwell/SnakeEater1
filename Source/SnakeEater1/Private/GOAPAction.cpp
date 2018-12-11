// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPAction.h"

void UGOAPAction::Activate(AAIController* controller)
{
	isActivated = true;
}

void UGOAPAction::Deactivate(AAIController* controller)
{
}

void UGOAPAction::SetPrec(FWorldProperty Prop)
{
	Preconditions.Add(Prop.key, Prop);
}

void UGOAPAction::SetEffect(FWorldProperty Prop)
{
	Effects.Add(Prop.key, Prop);
}

bool UGOAPAction::DoesSatisfyProperty(EPlannerSymbol Key, FWorldProperty TargetProperty)
{
	FWorldProperty val = Effects[Key];
	if (TargetProperty == val) { //override
		return true;
	}
	return false;
}
