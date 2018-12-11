// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActionCover.h"
#include "AIPlanningController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
//TODO:move to AIIdle.cpp
UTestActionIdle::UTestActionIdle()
{
	static ConstructorHelpers::FObjectFinder<UClass> Anim(TEXT("Class'/Game/ThirdPersonCPP/IdleAnim.IdleAnim_C'"));
	IdleAnim = Anim.Object;

	SetEffect(FWorldProperty(EPlannerSymbol::k_Idling , true));
	cost = 0;
}

void UTestActionIdle::Activate(AAIController* controller)
{
	
	AAIPlanningController* AIController = Cast<AAIPlanningController>(controller);
	if (!AIController)
	{
		return;
	}
	Super::Activate(controller);

	TArray<USkeletalMeshComponent*> Meshes;
	AIController->GetPawn()->GetComponents<USkeletalMeshComponent>(Meshes);
	for (auto & mesh : Meshes)
	{
		mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		mesh->SetAnimInstanceClass(IdleAnim);
		//mesh->Play(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("Idling"));
}
//TODO: move to AIPickupWeapon.cpp
UAIPickupWeapon::UAIPickupWeapon()
{
	SetEffect(FWorldProperty(EPlannerSymbol::k_WeaponArmed, true));
	cost = 1;
}


//TODO: move to AIAttack.cpp

UAIAttack::UAIAttack()
{
	static ConstructorHelpers::FObjectFinder<UClass> Anim(TEXT("Class'/Game/AnimStarterPack/RuntimeTestAnimBP.RuntimeTestAnimBP_C'"));
	AttackAnim = Anim.Object;

	SetEffect( FWorldProperty(EPlannerSymbol::k_TargetIsDead, true));
	//SetPrec(FWorldProperty(EPlannerSymbol::k_WeaponLoaded, true));
	//we need a better way to poll the actual world state
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
		mesh->SetAnimInstanceClass(AttackAnim);
		//mesh->Play(true);
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
	AAIPlanningController* AIController = Cast<AAIPlanningController>(controller);
	if (!AIController)
	{
		return false;
	}

	if (!AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetObj")))
	{
		return false;
	}

	if (AIController->GetBlackboardComponent()->GetValueAsInt(TEXT("AmmoCount")) <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH AMMO"))
		
		return false;
	}

	return true;
}


//////////////////////////

UAIFindAmmo::UAIFindAmmo() {
	SetEffect(FWorldProperty(EPlannerSymbol::k_WeaponLoaded, true));

	static ConstructorHelpers::FObjectFinder<UClass> Anim(TEXT("Class'/Game/ThirdPersonCPP/BasicMoveToAnimBP.BasicMoveToAnimBP_C'"));
	MoveToAnim = Anim.Object;

	cost = 1;
}

void UAIFindAmmo::Activate(AAIController* controller)
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
		mesh->SetAnimInstanceClass(MoveToAnim);
		//mesh->Play(true);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Would find ammo here"));
}

void UAIFindAmmo::Deactivate(AAIController* controller)
{
	Super::Deactivate(controller);

	UE_LOG(LogTemp,Error, TEXT("Should Deactivate here"))
}

bool UAIFindAmmo::IsValidAction(AAIController* controller)
{
	if (!controller)
	{
		return false;
	}
	AAIPlanningController* AIController = Cast<AAIPlanningController>(controller);
	if (AIController->GetBlackboardComponent()->GetValueAsInt(TEXT("AmmoCount")) > 0)
	{
		return false;
	}

	if (!AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("NearestAmmo")))
	{
		return false;
	}

	return true;
}

///////////////////

UAIWeaponLoadedAtom::UAIWeaponLoadedAtom()
{
	SetEffect(FWorldProperty(EPlannerSymbol::k_WeaponLoaded, true));
	cost = 1;
}

void UAIWeaponLoadedAtom::Activate(AAIController* controller)
{
	Super::Activate(controller);
	UE_LOG(LogTemp, Warning, TEXT("Activated"));
	isFinished = true;
}

void UAIWeaponLoadedAtom::Deactivate(AAIController* controller)
{
	Super::Deactivate(controller);
	UE_LOG(LogTemp, Warning, TEXT("deactivated"));
}

bool UAIWeaponLoadedAtom::IsValidAction(AAIController* controller)
{
	if (!controller)
	{
		return false;
	}
	AAIPlanningController* AIController = Cast<AAIPlanningController>(controller);
	if (AIController->GetBlackboardComponent()->GetValueAsInt(TEXT("AmmoCount")) == 0)
	{
		return false;
	}
	return true;
}