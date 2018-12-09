#pragma once

#include "CoreMinimal.h"
#include "PlannerSymbolDefinitions.generated.h"

UENUM()
enum class EPlannerSymbol : uint32
{
	//define precondition/effect symbols here as needed
	k_TESTSYM1,
	k_TESTSYM2,
	k_TESTSYM3,
	k_TESTSYM4,
	k_TargetIsDead,
	k_WeaponArmed,
	//should always be last
	NUM_SYMBOLS
};
