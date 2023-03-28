// Fill out your copyright notice in the Description page of Project Settings.


#include "GenMenu/ProjectToVT.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SProgressBar.h"
#include "Widgets/Layout/SWrapBox.h"
#include "DDToolsBPLibrary.h"


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
								.Text(FText::FromString(TEXT("Button 1")))
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("按钮1")))
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
								.Text(FText::FromString(TEXT("Button 1")))
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("按钮1")))
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
								.Text(FText::FromString(TEXT("Button 1")))
								.ContentPadding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("按钮1")))
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
								.Text(FText::FromString(TEXT("Button 1")))
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
				SNew(SProgressBar)
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
						.Text(FText::FromString(TEXT("按钮1")))
						.Font(FSlateFontInfo(FontPath, 24))
					]
				]
			]

            //EntTheCode
		];
}
