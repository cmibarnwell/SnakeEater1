#pragma once

#include "CoreMinimal.h"
#include "PlannerSymbolDefinitions.generated.h"

UENUM()
enum class EPlannerSymbol : uint32
{
	//define precondition/effect symbols here as needed
	k_AtNode,
	k_TargetIsFlushedOut,
	k_HealthIsLow,
	k_TargetIsAimingAtMe,
	k_TargetIsDead,
	k_WeaponArmed,
	k_WeaponLoaded,
	k_Idling,
	//should always be last
	NUM_SYMBOLS
};
