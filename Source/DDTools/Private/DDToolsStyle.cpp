// Fill out your copyright notice in the Description page of Project Settings.


#include "DDToolsStyle.h"
#include "FrameWork/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Runtime/Projects/Public/Interfaces/IPluginManager.h"


TSharedPtr<FSlateStyleSet> FDDToolsStyle::StyleInstance = NULL;

void FDDToolsStyle::Initialized()
{
	if (!StyleInstance.IsValid()) 
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FDDToolsStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}
FName FDDToolsStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DDToolsStyle"));
	return StyleSetName;
}


#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(Style->RootToContentDir(RelativePath,TEXT(".png")),__VA_ARGS__)
#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(Style->RootToContentDir(RelativePath,TEXT(".png")),__VA_ARGS_)
#define BORDER_BRUSH(RelativePath, ...) FSlateBorderBrush(Style->RootToContentDir(RelativePath,TEXT(".png")),__VA_ARGS__)
#define TTF_FONT(RelativePath, ...) FSlateFontInfo(Style->RootToContentDir(RelativePath,TEXT(".png")),__VA_ARGS__)
#define OTF_FONT(RelativePath, ...) FSlateFontInfo(Style->RootToContentDir(RelativePath,TEXT(".png")),__VA_ARGS__)

const FVector2D Icon16x16(16.0f,16.0f);
const FVector2D Icon20x20(20.0f,20.0f);
const FVector2D Icon40x40(40.0f,40.0f);


TSharedRef<class FSlateStyleSet> FDDToolsStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("DDToolsStyle"));
	FString PluginPath = IPluginManager::Get().FindPlugin("DDTools")->GetBaseDir() / TEXT("Resources");
	Style->SetContentRoot(PluginPath);
	Style->Set("DDTools.mountAction",new IMAGE_BRUSH(TEXT("DDTools_40x"),Icon40x40));
	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_BRUSH
#undef OTF_BRUSH



void FDDToolsStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized()) 
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FDDToolsStyle::Get()
{
	return *StyleInstance;
}



