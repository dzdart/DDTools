// Fill out your copyright notice in the Description page of Project Settings.


#include "GenMenu/ProjectToVT.h"



#define LOCTEXT_NAMESPACE "ProjectToVtName"
const FName ProjectName = TEXT("ProjectToVt");
ProjectToVT::ProjectToVT()
{

}

ProjectToVT::~ProjectToVT()
{
}

ProjectToVT& ProjectToVT::Get()
{
	static TUniquePtr<ProjectToVT> Singleton;
	if (!Singleton)
	{
		Singleton = MakeUnique<ProjectToVT>();
	}
	return *Singleton;
}

void ProjectToVT::GenMenu()
{
	FontPath = UDDToolsBPLibrary::GetDDToolsPath()+"Resources/SmileySans-Oblique.ttf";
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ProjectName, FOnSpawnTab::CreateRaw(this, &ProjectToVT::SpawnTab))
		.SetDisplayName(LOCTEXT("ProjectToVt", "ProjectToVt"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->TryInvokeTab(ProjectName);
}

TSharedRef<SDockTab> ProjectToVT::SpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestEditorStandaloneModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestEditorStandalone.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				.Padding(10.f)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.AutoHeight()
					.Padding(10.0f)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("单独修改")))
						.Font(FSlateFontInfo(FontPath, 24))
					]

					+SVerticalBox::Slot()
					.AutoHeight()
					.Padding(10.0f)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					
						[
							SAssignNew(EditableTextBox,SEditableTextBox)
							.Font(FSlateFontInfo(FontPath, 18))
							.Text(FText::FromString(TEXT("/Game")))
						]

					+SVerticalBox::Slot()
					.AutoHeight()
					.Padding(WrapBoxWidget,10.0f, WrapBoxWidget,10.0f)
					[
						SNew(SWrapBox)
						.UseAllottedWidth(true)
						.Orientation(Orient_Horizontal)
						+SWrapBox::Slot()
						.Padding(10.0f)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.ForceNewLine(false)

							[
								SNew(SButton)
								.ToolTipText(FText::FromString(TEXT("获取Game目录下的所有Tex资产设置为Vt\n对于尺寸为非2的幂次方的，将会设置填充到2的幂次方\n对于HDR相关的贴图，跳过不设置")))
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
	
								[
									SNew(STextBlock)
									.Margin(FMargin(5.0f))
									.Text(FText::FromString(TEXT("设置所有纹理为Vt")))
									.Font(FSlateFontInfo(FontPath, 24))
								]
							]
						+ SWrapBox::Slot()
							.Padding(10.0f)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.ForceNewLine(false)
							[
								SNew(SButton)
								.ToolTipText(FText::FromString(TEXT("获取Game目录下的所有Tex资产")))
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("设置所有材质为Vt")))
									.Font(FSlateFontInfo(FontPath, 24))
								]
							]
						+ SWrapBox::Slot()
							.Padding(10.0f)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.ForceNewLine(false)
							[
								SNew(SButton)
								.ToolTipText(FText::FromString(TEXT("获取Game目录下的所有的材质球和材质函数。\n将其引用的所有Tex和MatFunction都复制到/Game/ConvertAsset")))
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								//.OnClicked(this,&)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("修复所有材质引用到本地")))
									.Font(FSlateFontInfo(FontPath, 24))
								]
							]
						+ SWrapBox::Slot()
							.Padding(10.0f)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.ForceNewLine(false)
							[
								SNew(SButton)
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("按钮1")))
									.Font(FSlateFontInfo(FontPath, 24))
								]
							]

					]
					
				]
			]
			
			+SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SAssignNew(TextBlock,STextBlock)
				.Text(FText::FromString(TEXT("Test")))
				.Font(FSlateFontInfo(FontPath, 12))
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SAssignNew(ProgressBar, SProgressBar)
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(10.f)
				[
					SNew(SButton)
					.ContentPadding(FMargin(0.0f))
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("整体修改")))
						.Font(FSlateFontInfo(FontPath, 24))
					]
				]
			]

            //EntTheCode
		];
}

void ProjectToVT::SetAllTexUseVt()
{

}

void ProjectToVT::SetAllMatAndFunctionUsetVt()
{
}

void ProjectToVT::FixAllMatRefrenceToGame()
{
}

void ProjectToVT::GoAll()
{
}
