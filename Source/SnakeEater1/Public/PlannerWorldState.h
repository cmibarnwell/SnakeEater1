// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Set.h"
#include "PlannerWorldState.generated.h"


UENUM()
enum class EPlannerSymbol : uint32
{
	//define precondition/effect symbols here as needed
	k_TESTSYM1,
	k_TESTSYM2,
	k_TESTSYM3,
	k_TESTSYM4,
	//should always be last
	NUM_SYMBOLS
};

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
};
