// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "ContentBrowserModule.h"
#include "DDToolsBPLibrary.h"

class FDDToolsModule : public IModuleInterface
{
public:

	static FDDToolsModule& Get();
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void MountInit();


};
