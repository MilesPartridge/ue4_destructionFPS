// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IMPGAdestructionGameMode.h"
#include "IMPGAdestructionHUD.h"
#include "IMPGAdestructionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIMPGAdestructionGameMode::AIMPGAdestructionGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AIMPGAdestructionHUD::StaticClass();
}
