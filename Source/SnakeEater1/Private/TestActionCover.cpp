// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActionCover.h"

UTestActionIdle::UTestActionIdle()
{
	EPlannerSymbol Effect = EPlannerSymbol::k_Idling;
	Effects.Add(Effect, FWorldProperty(Effect, true));
	cost = 0;
}

UAIPickupWeapon::UAIPickupWeapon()
{
	Effects.Add(EPlannerSymbol::k_WeaponArmed, FWorldProperty(EPlannerSymbol::k_WeaponArmed, true));
}

UAIAttack::UAIAttack()
{
	Effects.Add(EPlannerSymbol::k_TargetIsDead, FWorldProperty(EPlannerSymbol::k_TargetIsDead, true));
	Preconditions.Add(EPlannerSymbol::k_WeaponLoaded, FWorldProperty(EPlannerSymbol::k_WeaponLoaded, true));
}
