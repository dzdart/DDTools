// Copyright Epic Games, Inc. All Rights Reserved.

#include "MaterialEditorTools.h"

#define LOCTEXT_NAMESPACE "FMaterialEditorTools"
void FMaterialEditorTools::OpenMaterialEditorToolsPlane()
{
	UE_LOG(LogTemp, Warning, TEXT("MaterialEditorToolsIsOpen!"));
}
void FMaterialEditorTools::StartupModule()
{
	RegisterMenuBar();
}

void FMaterialEditorTools::ShutdownModule()
{
}

void FMaterialEditorTools::RegisterMenuBar()
{
	IMaterialEditorModule& MaterialEditorModule = FModuleManager::LoadModuleChecked<IMaterialEditorModule>("MaterialEditor");
	TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender());
	MenuBarExtender->AddToolBarExtension(TEXT("Hierarchy"), EExtensionHook::After,nullptr, FToolBarExtensionDelegate::CreateRaw(this,&FMaterialEditorTools::AddMenuBar));

}

void FMaterialEditorTools::AddMenuBar(FToolBarBuilder& Builder)
{
	Builder.BeginSection(TEXT("Hierarchy"));
	{
		Builder.AddToolBarButton(
			FUIAction(
				FExecuteAction::CreateRaw(this, &FMaterialEditorTools::OpenMaterialEditorToolsPlane)
			),
			NAME_None,
			LOCTEXT("MaterialExitorTools", "MaterialExitorTools"),
			LOCTEXT("MaterialExitorTools", "MaterialExitorTools"),
			FSlateIcon(),
			EUserInterfaceActionType::Button,
			FName()

		);
	}
	Builder.EndSection();
	
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FMaterialEditorTools, MaterialEditorTools)