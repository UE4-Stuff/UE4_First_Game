// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom Hud class
	HUDClass = UPlayerHUD::StaticClass();
}

void AFPSGameMode::MissionSuccess(APawn* Pawn)
{
	if (Pawn) {
		Pawn->DisableInput(nullptr);
		OnMissionSuccess(Pawn);
		/*UPlayerHUD* Hud = Cast<UPlayerHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
		if (Hud && Hud->Message) {
			Hud->Message->RemoveFromParent();
		}*/
	}

}