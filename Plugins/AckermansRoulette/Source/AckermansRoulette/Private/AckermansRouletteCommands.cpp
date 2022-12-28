// Copyright Epic Games, Inc. All Rights Reserved.

#include "AckermansRouletteCommands.h"

#define LOCTEXT_NAMESPACE "FAckermansRouletteModule"

void FAckermansRouletteCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "AckermansRoulette", "Execute AckermansRoulette action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
