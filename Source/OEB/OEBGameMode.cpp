// Copyright Epic Games, Inc. All Rights Reserved.

#include "OEBGameMode.h"
#include "OEBCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOEBGameMode::AOEBGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_ThirdPersonCharacter_C"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
