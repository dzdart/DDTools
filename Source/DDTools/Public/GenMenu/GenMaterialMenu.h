// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DDTOOLS_API GenMaterialMenu
{
public:
	GenMaterialMenu();
	~GenMaterialMenu();
	static GenMaterialMenu& Get();
	void GenMenu();
};
