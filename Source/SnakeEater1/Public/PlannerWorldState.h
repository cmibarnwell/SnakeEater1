// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlannerWorldState.generated.h"


UENUM()
enum class EPlannerSymbol : uint32
{
	//define precondition/effect symbols here as needed
	k_TESTSYMBOL,

	//should always be last
	NUM_SYMBOLS
};

USTRUCT()
struct FWorldProperty 
{
	
	GENERATED_BODY();

	EPlannerSymbol key;
	typedef union property_value
	{
		uint32 iValue;
		bool bValue;
	} FPropValue;
	FPropValue value;

	friend bool operator==(const FWorldProperty &lhs, const FWorldProperty &rhs)
	{
		return lhs.value.bValue == rhs.value.bValue;
	}
	friend bool operator<(const FWorldProperty &lhs, const FWorldProperty &rhs)
	{
		return lhs.value.bValue < rhs.value.bValue;
	}
};

struct WorldPropertyKeyFuncs : DefaultKeyFuncs<FWorldProperty> {
	static uint32 GetKeyHash(FWorldProperty prop) { return static_cast<uint32>(prop.key); }
	static FWorldProperty GetSetKey(FWorldProperty prop) { return prop; }
};

/**
 * 
 */
USTRUCT()
struct FPlannerWorldState
{
	GENERATED_BODY()

	TSet<FWorldProperty, WorldPropertyKeyFuncs> Properties;

	bool IsSatisfied();
};
