// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AckermansRouletteStyle.h"

class FAckermansRouletteCommands : public TCommands<FAckermansRouletteCommands>
{
public:

	FAckermansRouletteCommands()
		: TCommands<FAckermansRouletteCommands>(TEXT("AckermansRoulette"), NSLOCTEXT("Contexts", "AckermansRoulette", "AckermansRoulette Plugin"), NAME_None, FAckermansRouletteStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
