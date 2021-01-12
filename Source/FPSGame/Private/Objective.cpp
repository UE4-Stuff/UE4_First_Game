// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AObjective::AObjective()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereComp = CreateDefaultSubobject<USphereComponent>("Hitbox");
	SphereComp->SetupAttachment(Mesh);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AObjective::BeginPlay()
{
	Super::BeginPlay();
	PlayFX();
}

// Called every frame
//void AObjective::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AObjective::NotifyActorBeginOverlap(AActor* OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayFX();
	
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character) {
		Character->HoldingObjective = true;
		Destroy();
	}
}

void AObjective::PlayFX() 
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
	UGameplayStatics::PlaySound2D(this, PickupSFX);
}