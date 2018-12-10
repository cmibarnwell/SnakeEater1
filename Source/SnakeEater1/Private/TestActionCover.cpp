// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActionCover.h"

UTestActionIdle::UTestActionIdle()
{
	EPlannerSymbol Effect = EPlannerSymbol::k_Idling;
	Effects.Add(Effect, FWorldProperty(Effect, true));
	cost = 0;
}

void UTestActionIdle::ExecuteAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Action: Idling"))
}
