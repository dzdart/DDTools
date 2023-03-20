// Fill out your copyright notice in the Description page of Project Settings.


#include "GenMenu/ContentBrowserMenu.h"
#include "DDToolsBPLibrary.h"
#include "DDToolsStyle.h"

ContentBrowserMenu::ContentBrowserMenu()
{
}

ContentBrowserMenu::~ContentBrowserMenu()
{
}

ContentBrowserMenu& ContentBrowserMenu::Get()
{
	static TUniquePtr<ContentBrowserMenu> Singleton;
	if (!Singleton)
	{
		Singleton = MakeUnique<ContentBrowserMenu>();
	}
	return *Singleton;
}

void ContentBrowserMenu::GenMenu()
{
	FDDToolsStyle::Initialized();
	FDDToolsStyle::ReloadTextures();
	CreateContentBrowserMenu();
}

void ContentBrowserMenu::CreateContentBrowserMenu()
{
	//获取到内容浏览器
	FContentBrowserModule& ContentBrowserMoudlue = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	//添加到代理数组内
	auto& MenuExtenderDelegates = ContentBrowserMoudlue.GetAllAssetViewContextMenuExtenders();
	MenuExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &ContentBrowserMenu::ContentBrowserAssetSelectionMenu));
	ContentBrowserAssetExtenderDelegateHandle = MenuExtenderDelegates.Last().GetHandle();
}

TSharedRef<FExtender> ContentBrowserMenu::ContentBrowserAssetSelectionMenu(const TArray<FAssetData>& AssetData)
{
	SelectAssetData = AssetData;
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("Delete", EExtensionHook::After, nullptr, FMenuExtensionDelegate::CreateRaw(this, &ContentBrowserMenu::MenuExtension));
	return MenuExtender.ToSharedRef();
}

void ContentBrowserMenu::MenuExtension(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddSubMenu(
		FText::FromString(TEXT("DDTools")),
		FText::FromString(TEXT("DDToolsBox")),
		FNewMenuDelegate::CreateRaw(this,&ContentBrowserMenu::CreateSubMenu),
		false,
		FSlateIcon(FDDToolsStyle::GetStyleSetName(),"DDTools.mountAction"),
		true,
		"DDTools"
	);
	
}

void ContentBrowserMenu::CreateSubMenu(FMenuBuilder& Builder)
{
	if (SelectAssetData[0].AssetClass==FName("Material")) 
	{
		CreateMaterialMenu(Builder);
	}
	if (SelectAssetData[0].AssetClass == FName("StaticMesh"))
	{
		CreateStaticMeshMenu(Builder);
	}
	if (SelectAssetData[0].AssetClass == FName("Texture2D"))
	{
		CreateTextureMenu(Builder);
	}

	if (SelectAssetData[0].AssetClass==FName("EditorUtilityWidgetBlueprint"))
	{
		CreateEditorUtilityWidgetBlueprint(Builder);
	}
}

void ContentBrowserMenu::CreateMaterialMenu(FMenuBuilder& Builder)
{
	/*Fix TextureSampler 16*/
	Builder.AddMenuEntry(
		FText::FromString(TEXT("FixTextureSanpler16")),
		FText::FromString(TEXT("修复材质球中贴图超过16张的报错")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &ContentBrowserMenu::FixTextureSampler16))
	);
	/*OpenMaterialRayTraceShadow*/
	Builder.AddMenuEntry(
		FText::FromString(TEXT("OpenMaterialRayTraceShadow")),
		FText::FromString(TEXT("开启材质球的光追阴影")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &ContentBrowserMenu::OpenMaterialRayTraceShadow))
	);
}

void ContentBrowserMenu::CreateTextureMenu(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FText::FromString(TEXT("SetTextureNoMipMap")),
		FText::FromString(TEXT("设置贴图无MipMap")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this,&ContentBrowserMenu::NoneFunction))
	);
}

void ContentBrowserMenu::CreateStaticMeshMenu(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FText::FromString(TEXT("RemoveStaticMeshAllLod")),
		FText::FromString(TEXT("设置静态网格体无LOD")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &ContentBrowserMenu::RemoveStaticMeshAllLod))
	);

	Builder.AddMenuEntry(
		FText::FromString(TEXT("AddLodNumTo8")),
		FText::FromString(TEXT("增加模型Lod数量到8")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this,&ContentBrowserMenu::AddMeshLodNumTo8))
	);
}
void ContentBrowserMenu::CreateEditorUtilityWidgetBlueprint(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FText::FromString(TEXT("AddEngineStar")),
		FText::FromString(TEXT("加入自动启动")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this,&ContentBrowserMenu::AddEngineStar))
	);

	Builder.AddMenuEntry(
		FText::FromString(TEXT("RemoveEngineStar")),
		FText::FromString(TEXT("移除自动启动")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &ContentBrowserMenu::RemoveEngineStar))
	);
}
/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                  这是一个分割线                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void ContentBrowserMenu::AddMeshLodNumTo8()
{
	TArray<UObject*> objects = AssetDatasToUobjects(SelectAssetData);
	for (UObject* item:objects)
	{
		if (UStaticMesh* mesh=Cast<UStaticMesh>(item)) 
		{
			UDDToolsBPLibrary::AddStaticMeshLodNumTo8(mesh);
		}
	}
}
void ContentBrowserMenu::AddEngineStar()
{
}
void ContentBrowserMenu::RemoveEngineStar()
{
}
void ContentBrowserMenu::RemoveStaticMeshAllLod()
{
	TArray<UObject*> objects = AssetDatasToUobjects(SelectAssetData);
	int LodNums = 0;
	for (UObject* item:objects)
	{
		if (UStaticMesh* mesh=Cast<UStaticMesh>(item))
		{
			UDDToolsBPLibrary::RemoveStaticMeshAllLod(mesh);
		}
	}
}
void ContentBrowserMenu::FixTextureSampler16()
{
	UDDToolsBPLibrary::SetMaterialTextureSampler(AssetDatasToUobjects(SelectAssetData), ESamplerSourceMode::SSM_Wrap_WorldGroupSettings);
}
void ContentBrowserMenu::OpenMaterialRayTraceShadow()
{
	TArray<UObject*> objects = AssetDatasToUobjects(SelectAssetData);
	for (UObject* item:objects) 
	{
		UDDToolsBPLibrary::SetMatRayShadow(Cast<UMaterial>(item),true);
		item->MarkPackageDirty();
	}
	
}

TArray<UObject*> ContentBrowserMenu::AssetDatasToUobjects(TArray<FAssetData> InAssetData)
{
	TArray<UObject*> Ret = TArray<UObject*>();
	UObject* TmpObjcet;
	for (FAssetData item : InAssetData)
	{
		TmpObjcet = LoadObject<UObject>(nullptr, *(item.ObjectPath.ToString()));
		if (TmpObjcet)
		{
			Ret.Add(TmpObjcet);
			TmpObjcet = nullptr;
		}

	}

	return Ret;
}

