// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* PickupFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundBase* PickupSFX;

	void PlayFX();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
