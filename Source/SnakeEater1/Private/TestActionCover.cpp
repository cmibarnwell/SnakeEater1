// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActionCover.h"
#include "AIPlanningController.h"
#include "Components/SkeletalMeshComponent.h"
//TODO:move to AIIdle.cpp
UTestActionIdle::UTestActionIdle()
{
	EPlannerSymbol Effect = EPlannerSymbol::k_Idling;
	Effects.Add(Effect, FWorldProperty(Effect, true));
	cost = 0;
}

//TODO: move to AIPickupWeapon.cpp
UAIPickupWeapon::UAIPickupWeapon()
{
	Effects.Add(EPlannerSymbol::k_WeaponArmed, FWorldProperty(EPlannerSymbol::k_WeaponArmed, true));
	cost = 1;
}


//TODO: move to AIAttack.cpp

UAIAttack::UAIAttack()
{
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> Anim(TEXT("AnimBlueprint'/Game/AnimStarterPack/RuntimeTestAnimBP.RuntimeTestAnimBP'"));
	AttackAnim = Anim.Object;

	Effects.Add(EPlannerSymbol::k_TargetIsDead, FWorldProperty(EPlannerSymbol::k_TargetIsDead, true));
	//Preconditions.Add(EPlannerSymbol::k_WeaponLoaded, FWorldProperty(EPlannerSymbol::k_WeaponLoaded, true));
	cost = 1;
}

void UAIAttack::Activate(AAIController* controller)
{
	Super::Activate(controller);
	AAIPlanningController* AIController = Cast<AAIPlanningController>(controller);
	if (!AIController)
	{
		return;
	}
	TArray<USkeletalMeshComponent*> Meshes;
	AIController->GetPawn()->GetComponents<USkeletalMeshComponent>(Meshes);
	for (auto & mesh : Meshes)
	{
		mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		mesh->SetAnimInstanceClass(AttackAnim->GetAnimBlueprintGeneratedClass());
		mesh->Play(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("ATTACK!!!"));
}

void UAIAttack::Deactivate(AAIController* controller)
{
	Super::Deactivate(controller);
	
	if (!controller)
	{
		return;
	}
}

bool UAIAttack::IsValidAction(AAIController* controller)
{
	if (!controller)
	{
		return false;
	}
	return true;
}