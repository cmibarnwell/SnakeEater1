// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SnakeEater1GameMode.h"
#include "SnakeEater1Character.h"
#include "UObject/ConstructorHelpers.h"

ASnakeEater1GameMode::ASnakeEater1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
