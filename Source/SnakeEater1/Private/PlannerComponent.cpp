// Fill out your copyright notice in the Description page of Project Settings.

#include "PlannerComponent.h"

// Sets default values for this component's properties
UPlannerComponent::UPlannerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("PLANNING COMPONENT INITIALIZED"));

	Planner = NewObject<UPlanner>();
	UTestActionCover* testAction = NewObject<UTestActionCover>();
	UTestActionChain* testAction2 = NewObject<UTestActionChain>();
	Planner->AddAction(testAction);
	Planner->AddAction(testAction2);
	needsPlan = true;
	/*
	TSharedPtr<UTestActionCover> testAction = TSharedPtr<UTestActionCover>(NewObject<UTestActionCover>());
	Planner->AddAction(testAction);
	currentAction = testAction;
	// ...
	*/
}

// Called when the game starts
void UPlannerComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UPlannerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if no plan exists, make one
	if (needsPlan)
	{
		needsPlan = false;
		UE_LOG(LogTemp, Warning, TEXT("NO ACTION SET"));
		FPlannerWorldState test_GoalState;
		test_GoalState.Properties.Add(FWorldProperty(EPlannerSymbol::k_TESTSYM4, true));
		if (Planner != nullptr)
		{
			bool success = Planner->SearchForGoal(test_GoalState);
			if (success)
			{
				Plan = Planner->SearchResultOnSuccess;
			}
		}
	}

	// ...
}

