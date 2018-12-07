// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActionCover.h"

UTestActionCover::UTestActionCover() 
{
	EPlannerSymbol Effect = EPlannerSymbol::k_TESTSYM3;
	Effects.Add(Effect, FWorldProperty(Effect, true));
	cost = 1;
}

void UTestActionCover::ExecuteAction()
{
	UE_LOG(LogTemp, Warning, TEXT("ACTION: TestActionCover"))
}

UTestActionChain::UTestActionChain()
{
	EPlannerSymbol Effect = EPlannerSymbol::k_TESTSYM4;
	EPlannerSymbol Precon = EPlannerSymbol::k_TESTSYM3;
	Effects.Add(Effect, FWorldProperty(Effect, true));
	Preconditions.Add(Precon, FWorldProperty(Precon, true));
	cost = 1;
}

void UTestActionChain::ExecuteAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Action: TestActionChain"))
}

