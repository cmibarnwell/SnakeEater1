// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPickup.h"
#include "SnakeEater1Character.h"

// Sets default values
AHealthPickup::AHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetSphereRadius(100.0f);
	SphereComponent->SetHiddenInGame(true);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::Heal);

}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPickup::Heal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ASnakeEater1Character* Player = Cast<ASnakeEater1Character>(OtherActor);

	Player->Heal(.5);
}