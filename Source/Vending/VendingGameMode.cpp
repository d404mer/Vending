// Copyright Epic Games, Inc. All Rights Reserved.

#include "VendingGameMode.h"
#include "VendingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVendingGameMode::AVendingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
