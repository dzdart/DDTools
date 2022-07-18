// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DDTOOLS_API GenLevelEditorMenu
{
public:
	GenLevelEditorMenu();
	~GenLevelEditorMenu();
	static GenLevelEditorMenu& Get();
	void GenMenu();
private:
	void LevelCreateMenu();
	void LevelAddMenuBarExtension(FMenuBarBuilder& Builder);
	void LevelMenuBarPullDown(FMenuBuilder& Builder);
private:
	void SwitchLanguage();
	void GoToProject();
};
