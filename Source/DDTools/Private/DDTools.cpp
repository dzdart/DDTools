// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDTools.h"
#include "GenMenu/GenLevelEditorMenu.h"
#include "GenMenu/ContentBrowserMenu.h"


#define LOCTEXT_NAMESPACE "FDDToolsModule"

FDDToolsModule& FDDToolsModule::Get()
{
	static TUniquePtr<FDDToolsModule> Singleton;
	if (!Singleton)
	{
		Singleton = MakeUnique<FDDToolsModule>();
	}
	return *Singleton;
}

void FDDToolsModule::StartupModule()
{

	GenLevelEditorMenu::Get().GenMenu();
	ContentBrowserMenu::Get().GenMenu();

	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this,&FDDToolsModule::MountInit);

}

void FDDToolsModule::ShutdownModule()
{
	
}

void FDDToolsModule::MountInit()
{
	FString ConfigPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectConfigDir(), "MountConfig.txt"));
	TArray<FString> MountList;
	bool ReadStat;
	UDDToolsBPLibrary::ReadTextFileToArray(ConfigPath, ReadStat,MountList);
	if (ReadStat)
	{
		for (FString item:MountList)
		{
			FPackageName::RegisterMountPoint("/Game/", *item);
		}
	}
}




#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDDToolsModule, DDTools)