// Fill out your copyright notice in the Description page of Project Settings.

#include "PlannerWorldState.h"

bool FPlannerWorldState::IsSatisfied()
{
	return Properties.Num() == 0;
}
