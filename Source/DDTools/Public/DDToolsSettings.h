// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DDToolsSettings.generated.h"

/**
 * 
 */
UCLASS(Config = DDToolsSettings, defaultconfig)
class DDTOOLS_API UDDToolsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Engine"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("DDToolsSettings"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("DDToolsSettings"); }

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
		FString PlayerName = "Default";

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
		float PlayerHealth = 100.0f;

	
};
