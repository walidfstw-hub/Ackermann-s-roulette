// Copyright Epic Games, Inc. All Rights Reserved.

#include "AckermansRoulette.h"
#include "AckermansRouletteStyle.h"
#include "AckermansRouletteCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Engine/StaticMeshActor.h"

static const FName AckermansRouletteTabName("AckermansRoulette");

#define LOCTEXT_NAMESPACE "FAckermansRouletteModule"

void FAckermansRouletteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAckermansRouletteStyle::Initialize();
	FAckermansRouletteStyle::ReloadTextures();

	FAckermansRouletteCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAckermansRouletteCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAckermansRouletteModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAckermansRouletteModule::RegisterMenus));
}

void FAckermansRouletteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAckermansRouletteStyle::Shutdown();

	FAckermansRouletteCommands::Unregister();
}

void FAckermansRouletteModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
        AActor* SMesh;

		FText DialogText = FText::FromString("Static Mesh Actor Not Found, Creating One");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		SMesh = AddActor(AStaticMeshActor::StaticClass());

}

void FAckermansRouletteModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAckermansRouletteCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAckermansRouletteCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

AActor* FAckermansRouletteModule::FindActor(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> FoundActors;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		UGameplayStatics::GetAllActorsOfClass(World, ActorClass, FoundActors);
		if (FoundActors.Num()>0)
		{
			return FoundActors[0];
		}
	}
	return nullptr;
}

AActor* FAckermansRouletteModule::AddActor(TSubclassOf<AActor> ActorClass)
{
	ULevel* Level = GEditor->GetEditorWorldContext().World()->GetCurrentLevel();

	GEditor->AddActor(Level, ActorClass, FTransform());

	return nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAckermansRouletteModule, AckermansRoulette)