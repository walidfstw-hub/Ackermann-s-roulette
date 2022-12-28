// Copyright Epic Games, Inc. All Rights Reserved.

#include "AckermansRouletteStyle.h"
#include "AckermansRoulette.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAckermansRouletteStyle::StyleInstance = nullptr;

void FAckermansRouletteStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAckermansRouletteStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAckermansRouletteStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AckermansRouletteStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAckermansRouletteStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AckermansRouletteStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AckermansRoulette")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AckermansRoulette.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FAckermansRouletteStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAckermansRouletteStyle::Get()
{
	return *StyleInstance;
}
