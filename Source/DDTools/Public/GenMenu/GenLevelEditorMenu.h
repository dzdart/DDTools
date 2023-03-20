// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor.h"
#include "IPlatformFilePak.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"

/**
 * 
 */
class DDTOOLS_API GenLevelEditorMenu
{
public:
	//UEditorUtilitySubsystem* EditorSubSys = UEditorUtilitySubsystem::UEditorUtilitySubsystem().Initialize(FSubsystemCollectionBase& Collection);
	
	GenLevelEditorMenu();
	~GenLevelEditorMenu();
	static GenLevelEditorMenu& Get();
	void GenMenu();
private:
	void LevelCreateMenu();
	void LevelAddMenuBarExtension(FMenuBarBuilder& Builder);
	void LevelMenuBarPullDown(FMenuBuilder& Builder);
private:
	
	void MountAsset();
	void SwitchLanguage();
	void GoToProject();
	void OpenTab();
};
