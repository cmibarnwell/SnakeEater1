// Fill out your copyright notice in the Description page of Project Settings.

#include "PainVolume.h"
#include "SnakeEater1Character.h"

// Sets default values
APainVolume::APainVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bActorInside = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetBoxExtent(FVector(20, 10, 5), false);
	BoxComponent->SetHiddenInGame(false);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APainVolume::DealDamage);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APainVolume::EndDamage);

}

// Called when the game starts or when spawned
void APainVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APainVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APainVolume::DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ASnakeEater1Character* Player = Cast<ASnakeEater1Character>(OtherActor);
	bActorInside = true;


		Player->DealDamage(.2);
}

void APainVolume::EndDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bActorInside = false;
}

