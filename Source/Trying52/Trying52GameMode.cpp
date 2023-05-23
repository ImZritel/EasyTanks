// Copyright Epic Games, Inc. All Rights Reserved.

#include "Trying52GameMode.h"
#include "Trying52PlayerController.h"
#include "Trying52Character.h"
#include "UObject/ConstructorHelpers.h"

ATrying52GameMode::ATrying52GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATrying52PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}