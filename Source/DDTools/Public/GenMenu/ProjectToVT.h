// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

/**
 * 
 */
class DDTOOLS_API ProjectToVT
{
public:
	ProjectToVT();
	~ProjectToVT();
	static ProjectToVT& Get();
	void GenMenu();
	TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& SpawnTabArgs);
	FString FontPath;
};
