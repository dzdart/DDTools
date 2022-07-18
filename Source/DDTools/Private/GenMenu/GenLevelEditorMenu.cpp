// Fill out your copyright notice in the Description page of Project Settings.


#include "GenMenu/GenLevelEditorMenu.h"
#include "LevelEditor.h"
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

	Builder.AddMenuEntry(FText::FromString("GoToProject"),
		FText::FromString("GoToProject"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &GenLevelEditorMenu::GoToProject)
		)
	);
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
	system("explorer https://github.com/dzdart/MegascansPlugin/");
}

