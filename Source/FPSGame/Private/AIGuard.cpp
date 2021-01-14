// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>("PawnSense");
	PawnSense->OnSeePawn.AddDynamic(this, &AAIGuard::PawnSeen);
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void PawnSeen(APawn* SeenPawn) 
{
	if (SeenPawn)
	{

		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
	}
	
}