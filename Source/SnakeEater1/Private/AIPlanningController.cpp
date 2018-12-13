// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlanningController.h"

AAIPlanningController::AAIPlanningController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	PrimaryActorTick.bStartWithTickEnabled = true;
	planComp = CreateDefaultSubobject<UPlannerComponent>("planner");
	planComp->Activate();

	CurrentWorldState.Reserve((uint32)EPlannerSymbol::NUM_SYMBOLS);
	for (uint32 i = 0; i < (uint32)EPlannerSymbol::NUM_SYMBOLS; ++i)
	{
		CurrentWorldState.Add(FWorldProperty((EPlannerSymbol)i, false));
	}
	NeedNewPlan = false;
	isPlanning = false;

	FPlannerWorldState attack;
	attack.SetProp( FWorldProperty(EPlannerSymbol::k_TargetIsDead, true));
	Goals.Add(attack);
	FPlannerWorldState foundAmmo;
	foundAmmo.SetProp(FWorldProperty(EPlannerSymbol::k_WeaponLoaded, true));
	Goals.Add(foundAmmo);
	FPlannerWorldState idle;
	idle.SetProp(FWorldProperty(EPlannerSymbol::k_Idling, true));
	Goals.Add(idle);
}

void AAIPlanningController::BeginPlay() 
{
	Super::BeginPlay();

	UBlackboardData* BlackboardAsset = NewObject<UBlackboardData>();
	BlackboardAsset->UpdatePersistentKey<UBlackboardKeyType_Object>(TEXT("TargetObj"));
	BlackboardAsset->UpdatePersistentKey<UBlackboardKeyType_Object>(TEXT("NearestAmmo"));
	BlackboardAsset->UpdatePersistentKey<UBlackboardKeyType_Int>(TEXT("AmmoCount"));
	UseBlackboard(BlackboardAsset, Blackboard);

	planComp->AddAction(NewObject<UAIAttack>());
	planComp->AddAction(NewObject<UAIFindAmmo>());
	//planComp->AddAction(NewObject<UAIWeaponLoadedAtom>());
	planComp->AddAction(NewObject<UTestActionIdle>());
}

void AAIPlanningController::Tick(float deltatime)
{
	Super::Tick(deltatime);

	//run current state if not planning


	//make this an event or something
	//if we have a plan
		//if our top action is not activated, activate it
		//if its complete, get the next action
		//if it failed, flag REPLAN
	//if flagged REPLAN
		//reevaluate goals
		//check goals by priority
		//attempt to make plan
	if (NeedNewPlan && !isPlanning)
	{
		UE_LOG(LogTemp, Error, TEXT("Making new Plan"));
		
		isPlanning = true; 
		//make sure there are no race conditions
		ReevaluateGoals();
		for (auto & goal : Goals)
		{
			bool success = planComp->SearchForGoal(goal, CurrentWorldState);
			if (success)
			{
				if (currentAction && !currentAction->isFinished)
				{
					currentAction->Deactivate(this);
				}
				NeedNewPlan = false;
				currentAction = planComp->GetTopAction();
				currentAction->Activate(this);
				break;
			}
		}
		isPlanning = false;
	} 
	if (currentAction && currentAction->isFinished)
	{
		currentAction->Deactivate(this);
		currentAction = planComp->GetTopAction();
		if (currentAction)
		{
			currentAction->Activate(this);
		}
		else
		{
			NeedNewPlan = true;
		}
	}
}

void AAIPlanningController::SetTarget(const FName &KeyName, AActor* Actor)
{
	GetBlackboardComponent()->SetValueAsObject(KeyName, Actor);
}

void AAIPlanningController::TrackTarget(bool Track)
{
	if (Track) {
		UObject* target = GetBlackboardComponent()->GetValueAsObject(TEXT("TargetObj"));
		if (target)
		{
			AActor* actor = Cast<AActor>(target);
			if (actor)
			{
				SetFocus(actor);
			}
		}
	}
	else
	{
		SetFocus(nullptr);
	}
}

void AAIPlanningController::SetActionComplete(bool IsActionComplete)
{
	if (currentAction)
	{
		currentAction->isFinished = true;
	}
}
void AAIPlanningController::OnActionComplete()
{
	currentAction->Deactivate(this);
}
void AAIPlanningController::ReevaluateGoals()
{

}