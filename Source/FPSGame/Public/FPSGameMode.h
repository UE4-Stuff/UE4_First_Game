// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Spectate")
	TSubclassOf<AActor> SpectatorCamClass;

public:

	AFPSGameMode();

	void MissionSuccess(APawn* pawn);

	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void OnMissionSuccess(APawn* pawn);
};



