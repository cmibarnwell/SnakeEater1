// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Set.h"
#include "PlannerSymbolDefinitions.h"
#include "PlannerWorldState.generated.h"



USTRUCT()
struct FWorldProperty 
{
	
	GENERATED_BODY();

	FWorldProperty() { };
	FWorldProperty(EPlannerSymbol key, bool bVal);

	UPROPERTY()
	EPlannerSymbol key;

	bool value;

	friend bool operator==(const FWorldProperty &lhs, const FWorldProperty &rhs)
	{
		return lhs.value == rhs.value;
	}
};

struct WorldPropertyKeyFuncs : DefaultKeyFuncs<FWorldProperty> {
	typedef typename TCallTraits<FWorldProperty>::ParamType KeyInitType;
	typedef typename TCallTraits<FWorldProperty>::ParamType ElementInitType;

	static uint32 GetKeyHash(KeyInitType prop) { return static_cast<uint32>(prop.key); }
	static KeyInitType GetSetKey(ElementInitType prop) { return prop; }
	static bool Matches(KeyInitType A, KeyInitType B) { return A.key == B.key; }
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

	void SetProp(FWorldProperty newProp) { Properties.Add(newProp); }
};
