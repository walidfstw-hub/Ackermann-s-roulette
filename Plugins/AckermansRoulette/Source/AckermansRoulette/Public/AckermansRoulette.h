// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Http.h"
#include "Engine/DataTable.h"

class FToolBarBuilder;
class FMenuBuilder;
class DataTable;

/*USTRUCT(BlueprintType)
struct FDieWasserspinne : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TAssetPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 numberForStaticMesh;
}; */

class FAckermansRouletteModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UDataTable* noOfMeshDataTable;
	
private:

	void RegisterMenus();
	AActor* FindActor(TSubclassOf<AActor> ActorClass);
	AActor* AddActor(TSubclassOf<AActor> ActorClass);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
      void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
