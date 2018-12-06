// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"

/**
 * 
 */
class SNAKEEATER1_API Plan
{
public:
	Plan();
	~Plan();

	UGOAPAction* m_currentAction;
	Plan* m_nextAction;
};
