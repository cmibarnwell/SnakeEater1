// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "PlannerWorldState.h"
#include "Animation/AnimBlueprint.h"
#include "ConstructorHelpers.h"
#include "TestActionCover.generated.h"

UCLASS()
class SNAKEEATER1_API UTestActionIdle : public UGOAPAction
{
	GENERATED_BODY()

	UPROPERTY()
	UClass* IdleAnim;
public:
	UTestActionIdle();
	
	virtual void Activate(AAIController* controller) override;
};

///////////////////////////////////////////////

UCLASS()
class SNAKEEATER1_API UAIPickupWeapon : public UGOAPAction
{
	GENERATED_BODY()

public:
	UAIPickupWeapon();
};

///////////////////////////////////////////////

UCLASS()
class SNAKEEATER1_API UAIAttack : public UGOAPAction
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UClass* AttackAnim;
public:
	UAIAttack();

	virtual void Activate(AAIController* controller) override;
	virtual void Deactivate(AAIController* controller) override;
	virtual bool IsValidAction(AAIController* controller) override;
};

/////////////////////////////////////////////////

UCLASS()
class SNAKEEATER1_API UAIFindAmmo : public UGOAPAction
{
	GENERATED_BODY()

	UPROPERTY()
	UClass* MoveToAnim;
public:
	UAIFindAmmo();

	virtual void Activate(AAIController* controller) override;
	virtual void Deactivate(AAIController* controller) override;
	virtual bool IsValidAction(AAIController* controller) override;
};

////////////////////////////////

UCLASS()
class SNAKEEATER1_API UAIWeaponLoadedAtom : public UGOAPAction
{
	GENERATED_BODY()

public:
	UAIWeaponLoadedAtom();

	virtual void Activate(AAIController* controller) override;
	virtual void Deactivate(AAIController* controller) override;
	virtual bool IsValidAction(AAIController* controller) override;
};