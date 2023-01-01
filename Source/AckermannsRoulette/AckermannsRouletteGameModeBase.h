// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "AckermannsRouletteGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class ACKERMANNSROULETTE_API AAckermannsRouletteGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void StartPlay() override;

private:

};
