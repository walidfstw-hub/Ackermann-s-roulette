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
#include "Json.h"
#include "UObject/ConstructorHelpers.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "Json.h"
#include "UObject/ConstructorHelpers.h"


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
	
	// HTTP Request Code Here
	UE_LOG(LogTemp, Display, TEXT("Came here !!"));
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindRaw(this, &FAckermansRouletteModule::OnResponseReceived);
	Request->SetURL("http://www.randomnumberapi.com/api/v1.0/random?min=0&max=10&count=1");
	Request->SetVerb("GET");
	Request->ProcessRequest();

	// HTTP Request Code Ends Here

        AActor* SMesh;
		FText DialogText = FText::FromString("Static Mesh Actor will be Generated !");
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

void FAckermansRouletteModule::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	// FString Responsed = *Response->GetContentAsString();
	UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAckermansRouletteModule, AckermansRoulette)