// Fill out your copyright notice in the Description page of Project Settings.


#include "GenMenu/GenMaterialMenu.h"

GenMaterialMenu::GenMaterialMenu()
{
}

GenMaterialMenu::~GenMaterialMenu()
{
}

GenMaterialMenu& GenMaterialMenu::Get()
{
	static TUniquePtr<GenMaterialMenu> Singleton;
	if (!Singleton)
	{
		Singleton = MakeUnique<GenMaterialMenu>();
	}
	return *Singleton;
}

void GenMaterialMenu::GenMenu()
{

}
