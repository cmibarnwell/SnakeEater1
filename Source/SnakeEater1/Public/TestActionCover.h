// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "PlannerWorldState.h"
#include "TestActionCover.generated.h"

UCLASS()
class SNAKEEATER1_API UTestActionIdle : public UGOAPAction
{
	GENERATED_BODY()

public:
	UTestActionIdle();
};

UCLASS()
class SNAKEEATER1_API UAIPickupWeapon : public UGOAPAction
{
	GENERATED_BODY()

public:
	UAIPickupWeapon();
};

UCLASS()
class SNAKEEATER1_API UAIAttack : public UGOAPAction
{
	GENERATED_BODY()

public:
	UAIAttack();
};