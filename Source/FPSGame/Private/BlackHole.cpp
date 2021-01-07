// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "FPSProjectile.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EventHorizon = CreateDefaultSubobject<USphereComponent>("EventHorizon");
	EventHorizon->SetupAttachment(Mesh);
	EventHorizon->SetSphereRadius(16);
	EventHorizon->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::EHEntered);

	Disk = CreateDefaultSubobject<USphereComponent>("Disk");
	Disk->SetupAttachment(Mesh);
	Disk->SetSphereRadius(3000);
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find all overlapping components that can collide and may be physically simulating.
	TArray<UPrimitiveComponent*> OverlappingComps;
	Disk->GetOverlappingComponents(OverlappingComps);

	for (UPrimitiveComponent* PrimComp : OverlappingComps)
	{
		if (PrimComp && PrimComp->IsSimulatingPhysics() || Cast<AFPSProjectile>(PrimComp->GetOwner()))
		{
			const float SphereRadius = Disk->GetScaledSphereRadius();
			const float ForceStrength = -2000; // Negative value to make it pull towards the origin instead of pushing away

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}


}

void ABlackHole::EHEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor) {
		OtherActor->Destroy();
	}
}


