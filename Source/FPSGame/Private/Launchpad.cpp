// Fill out your copyright notice in the Description page of Project Settings.


#include "Launchpad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ALaunchpad::ALaunchpad()
{
	PrimaryActorTick.bCanEverTick = false;

	Pad = CreateDefaultSubobject<UStaticMeshComponent>("Pad");
	RootComponent = Pad;

	Arrow = CreateDefaultSubobject<UStaticMeshComponent>("Arrow");
	Arrow->SetupAttachment(Pad);

	Hitbox = CreateDefaultSubobject<UBoxComponent>("Hitbox");
	Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Hitbox->SetCollisionResponseToAllChannels(ECR_Ignore);
	Hitbox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Hitbox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ALaunchpad::Overlap);
	Hitbox->SetupAttachment(Pad);
}

// Called when the game starts or when spawned
void ALaunchpad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaunchpad::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		Character->LaunchCharacter(FVector(0.0f, 5000.0f, 5000.0f), true, true);
		//OtherComp->AddImpulse(FVector(0.0f, 5000.0f, 5000.0f));
		//OtherComp->Add
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSFX);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics() ) {
		OtherComp->AddImpulse(FVector(0.0f, 5000.0f, 5000.0f), NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSFX);
	}

}
// Called every frame
//void ALaunchpad::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

