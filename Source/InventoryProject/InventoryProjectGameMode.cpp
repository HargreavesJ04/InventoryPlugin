// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryProjectGameMode.h"
#include "InventoryProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventoryProjectGameMode::AInventoryProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
