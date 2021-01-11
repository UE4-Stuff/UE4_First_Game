// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launchpad.generated.h"

UCLASS()
class FPSGAME_API ALaunchpad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchpad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* Pad;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Arrow;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UBoxComponent* Hitbox;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* LaunchFX;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* LaunchSFX;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Magnitude;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Angle;

	UFUNCTION()
	void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
