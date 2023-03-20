// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Modules/ModuleManager.h"
#include "ContentBrowserModule.h"
#include "CoreMinimal.h"

/**
 * 
 */
class DDTOOLS_API ContentBrowserMenu
{
public:
	ContentBrowserMenu();
	~ContentBrowserMenu();
	static ContentBrowserMenu& Get();
	void GenMenu();

	void CreateContentBrowserMenu();
	//void RemoveContentBrowserMenu();
private:
	TArray<FAssetData> SelectAssetData;
	FContentBrowserMenuExtender_SelectedAssets ContentBrowserFolderExtenderDelegate;
	FDelegateHandle ContentBrowserAssetExtenderDelegateHandle;

	TSharedRef<FExtender>ContentBrowserAssetSelectionMenu(const TArray<FAssetData>& AssetData);
	void MenuExtension(FMenuBuilder& MenuBuilder);
	void CreateSubMenu(FMenuBuilder& Builder);

	void NoneFunction() {};

	void CreateMaterialMenu(FMenuBuilder& Builder);
	void CreateTextureMenu(FMenuBuilder& Builder);
	void CreateStaticMeshMenu(FMenuBuilder& Builder);
	void CreateEditorUtilityWidgetBlueprint(FMenuBuilder& Builder);

	TArray<UObject*> AssetDatasToUobjects(TArray<FAssetData> InAssetData);

	/*CreateEditorUtilityWidgetBlueprint*/
	void AddEngineStar();
	void RemoveEngineStar();

	/*StaticMeshFunctions*/
	void RemoveStaticMeshAllLod();
	void AddMeshLodNumTo8();

	/*Texture2DFunctions*/
	void FixTextureSampler16();

	/*MaterialFunctions*/
	void OpenMaterialRayTraceShadow();
};
