// Fill out your copyright notice in the Description page of Project Settings.


#include "GenMenu/GenLevelEditorMenu.h"
#include "LevelEditor.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "Engine/Classes/Kismet/KismetInternationalizationLibrary.h"
#include "Engine/Classes/Materials/MaterialInterface.h"


#define LOCTEXT_NAMESPACE "GenLevelEditorMenu"


GenLevelEditorMenu::GenLevelEditorMenu()
{
}

GenLevelEditorMenu::~GenLevelEditorMenu()
{
}

GenLevelEditorMenu& GenLevelEditorMenu::Get()
{
	static TUniquePtr<GenLevelEditorMenu> Singleton;
	if (!Singleton) 
	{
		Singleton = MakeUnique<GenLevelEditorMenu>();
	}
	return *Singleton;
}

void GenLevelEditorMenu::GenMenu()
{

	LevelCreateMenu();
}

void GenLevelEditorMenu::LevelCreateMenu()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender());
	MenuBarExtender->AddMenuBarExtension("Help",
		EExtensionHook::After, nullptr, FMenuBarExtensionDelegate::CreateRaw(this, &GenLevelEditorMenu::LevelAddMenuBarExtension));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);
}

void GenLevelEditorMenu::LevelAddMenuBarExtension(FMenuBarBuilder& Builder)
{
	Builder.AddPullDownMenu(
		LOCTEXT("PullMenu", "DDTools"),
		LOCTEXT("PullMenu Tips", "DDTools Menu"),
		FNewMenuDelegate::CreateRaw(this, &GenLevelEditorMenu::LevelMenuBarPullDown)
		

	);
}

void GenLevelEditorMenu::LevelMenuBarPullDown(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FText::FromString("SwitchLanguage"),
		FText::FromString("SwitchLanguage"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &GenLevelEditorMenu::SwitchLanguage)
		)
	);

	Builder.AddMenuEntry(FText::FromString("MountAsset"),
		FText::FromString("MountAsset"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &GenLevelEditorMenu::MountAsset)
		)
	);

	Builder.AddMenuEntry(FText::FromString("GoToProject"),
		FText::FromString("GoToProject"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &GenLevelEditorMenu::GoToProject)
		)
	);
	AutoRegisterMenu(Builder);
}




/*菜单相关方法*/
void GenLevelEditorMenu::SwitchLanguage()
{
	FString NowLanguage = UKismetInternationalizationLibrary::GetCurrentLanguage();
	if (NowLanguage == L"en")
	{
		UKismetInternationalizationLibrary::SetCurrentLanguage("zh_cn", false);
	}
	if (NowLanguage == L"zh-Cn")
	{
		UKismetInternationalizationLibrary::SetCurrentLanguage("en", false);
	}
}

void GenLevelEditorMenu::GoToProject()
{
	system("explorer https://github.com/dzdart/DDTools");
}



void GenLevelEditorMenu::OpenTab(FString BpPaths)
{
	UEditorUtilityWidgetBlueprint* BPW = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr,*BpPaths);
	GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>()->SpawnAndRegisterTab(BPW);
}

void GenLevelEditorMenu::RunCmd(FString Commadns)
{
	UDDToolsBPLibrary::RunCmd(Commadns);
}

void GenLevelEditorMenu::AutoRegisterMenu(FMenuBuilder& Builder)
{
	FString PluginDir = FPaths::GetPath(FModuleManager::Get().GetModuleFilename("DDTools"));
	PluginDir = PluginDir.Replace(TEXT("Binaries/Win64"), TEXT(""));
	AutoRegisterMenuConfigPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, "Config", "AutoRegisterMenu.txt"));

	TArray<FString> ConfigList;
	FFileHelper::LoadFileToStringArray(ConfigList, *AutoRegisterMenuConfigPath);
	if (ConfigList.Num()>0)
	{
		for (FString item:ConfigList) 
		{
			TArray<FString> SplitArray;
			item.ParseIntoArray(SplitArray,TEXT("="));
			if (SplitArray.Num()==3)
			{
				if (SplitArray[0]=="UMG")
				{
					if (LoadObject<UObject>(nullptr, *SplitArray[2]))
					{
						Builder.AddMenuEntry(FText::FromString(SplitArray[1]),
							FText::FromString(SplitArray[1]),
							FSlateIcon(),
							FUIAction(FExecuteAction::CreateRaw(this, &GenLevelEditorMenu::OpenTab, SplitArray[2])
							)
						);
					}
				}
				if (SplitArray[0]=="CMD")
				{
					Builder.AddMenuEntry(FText::FromString(SplitArray[1]),
						FText::FromString(SplitArray[1]),
						FSlateIcon(),
						FUIAction(FExecuteAction::CreateRaw(this, &GenLevelEditorMenu::RunCmd, SplitArray[2])
						)
					);
				}
				
			}
		}
	}
}

void GenLevelEditorMenu::MountAsset()
{
	UEditorUtilityWidgetBlueprint* BPW = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, *FString("/Script/Blutility.EditorUtilityWidgetBlueprint'/DDTools/Mount/MountMain.MountMain'"));
	GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>()->SpawnAndRegisterTab(BPW);
}