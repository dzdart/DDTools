// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "ContentBrowserModule.h"
#include "Editor/MaterialEditor/Public/MaterialEditorModule.h"

class FMaterialEditorTools : public IModuleInterface
{
private:
	void OpenMaterialEditorToolsPlane();
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void RegisterMenuBar();
	void AddMenuBar(FToolBarBuilder& Builder);
};
