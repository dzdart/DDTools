// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor.h"
#include "IPlatformFilePak.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"
#include "HAL/IPlatformFileModule.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "../DDToolsBPLibrary.h"
#include "ProjectToVT.h"
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
	FString AutoRegisterMenuConfigPath;
private:
	
	void AutoRegisterMenu(FMenuBuilder& Builder);
	void ProjectVt();
	void MountAsset();
	void SwitchLanguage();
	void GoToProject();
	void OpenTab(FString BpPaths);
	void RunCmd(FString Commadns);
};
