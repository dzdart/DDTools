// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SProgressBar.h"
#include "Widgets/Layout/SWrapBox.h"
#include "DDToolsBPLibrary.h"

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
private:
	float WrapBoxWidget = 200.0f;
	TSharedPtr<SEditableTextBox> EditableTextBox;
	TSharedPtr<SProgressBar> ProgressBar;
	TSharedPtr<STextBlock> TextBlock;

	

private:
	/*ButtonFunction*/
	void SetAllTexUseVt();
	void SetAllMatAndFunctionUsetVt();
	void FixAllMatRefrenceToGame();
	void GoAll();
};
