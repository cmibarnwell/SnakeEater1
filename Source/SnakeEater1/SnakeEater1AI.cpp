// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeEater1AI.h"

// Sets default values
ASnakeEater1AI::ASnakeEater1AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakeEater1AI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeEater1AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakeEater1AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

