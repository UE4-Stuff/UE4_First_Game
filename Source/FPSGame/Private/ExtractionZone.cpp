// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Hitbox = CreateDefaultSubobject<UBoxComponent>("Hitbox");
	Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Hitbox->SetCollisionResponseToAllChannels(ECR_Ignore);
	Hitbox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Hitbox->SetBoxExtent(FVector(200.0f));
	SetRootComponent(Hitbox);

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::ZoneEntered);
	//Hitbox->SetHiddenInGame(false);

	Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
	Decal->DecalSize = FVector(200.0f);
	Decal->SetupAttachment(Hitbox);
}

// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AExtractionZone::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AExtractionZone::ZoneEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character) 
	{
		if (Character->HoldingObjective) 
		{
			AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (GM) 
			{
				GM->MissionSuccess(Character);
			}
		}
		else {
			UGameplayStatics::PlaySound2D(this, NoObjectiveSfx);
		}
	}

}

