// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDTools.h"
#include "GenMenu/GenLevelEditorMenu.h"
#include "GenMenu/ContentBrowserMenu.h"
#include "GenMenu/GenMaterialMenu.h"
#define LOCTEXT_NAMESPACE "FDDToolsModule"

void FDDToolsModule::StartupModule()
{

	GenLevelEditorMenu::Get().GenMenu();
	ContentBrowserMenu::Get().GenMenu();
	GenMaterialMenu::Get().GenMenu();
}

void FDDToolsModule::ShutdownModule()
{
	
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDDToolsModule, DDTools)