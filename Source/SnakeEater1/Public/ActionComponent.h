#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GOAPAction.h"

#include "ActionComponent.generated.h"

UCLASS()
class SNAKEEATER1_API UActionComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
	
protected:
	UPROPERTY()
	UGOAPAction* currentAction;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetAction(UGOAPAction* nextAction);
};