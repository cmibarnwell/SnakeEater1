// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPAction.h"

bool UGOAPAction::DoesSatisfyProperty(EPlannerSymbol Key, FWorldProperty TargetProperty)
{
	FWorldProperty val = Effects[Key];
	if (TargetProperty == val) { //override
		return true;
	}
	return false;
}
