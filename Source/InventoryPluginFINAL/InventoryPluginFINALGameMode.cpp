// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryPluginFINALGameMode.h"
#include "InventoryPluginFINALCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventoryPluginFINALGameMode::AInventoryPluginFINALGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
