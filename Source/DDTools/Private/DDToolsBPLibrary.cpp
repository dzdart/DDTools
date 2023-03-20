// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDToolsBPLibrary.h"
#include "DDTools.h"
#include "HAL/IPlatformFileModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "MainFrame/Public/Interfaces/IMainFrameModule.h"

UDDToolsBPLibrary::UDDToolsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

#pragma optimize("", off)

//设置材质变量的名字和组信息
void UDDToolsBPLibrary::SetMaterialParameterName(UMaterialExpressionScalarParameter* ME, FName Name, FName Group)
{
	//UMaterialExpression* dd;

	//UMaterialExpressionScalarParameter* MESP = dynamic_cast <UMaterialExpression>(dd);
	if (ME != nullptr) {
		ME->SetParameterName(Name);
		ME->Group = Group;
	}


}

//设置材质是否启用光追阴影
UMaterial* UDDToolsBPLibrary::SetMatRayShadow(UMaterial* Mat, bool on)
{
	if (Mat != nullptr) {
		if (Mat->BlendMode == BLEND_Translucent) {

			if (on) {
				Mat->bCastRayTracedShadows = 1;
			}
			else {
				Mat->bCastRayTracedShadows = 1;
			}
			Mat->PreEditChange(nullptr);
			Mat->PostEditChange();
			return Mat;
		}
		else {
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}


}

void UDDToolsBPLibrary::SetMaterialTextureSampler(TArray<UObject*> Objects, ESamplerSourceMode Type)
{
	for (auto item : Objects)
	{
		UMaterial* mat = Cast<UMaterial>(item);
		if (mat) {
			
			for (UMaterialExpression* UME : mat->GetExpressions())
			{
				if (UMaterialExpressionTextureSample* tmpTME = Cast<UMaterialExpressionTextureSample>(UME)) { tmpTME->SamplerSource = (Type); }
				if (UMaterialExpressionTextureSampleParameter* tmpUME = Cast<UMaterialExpressionTextureSampleParameter>(UME)) { tmpUME->SamplerSource = (Type); }
				if (UMaterialExpressionMaterialFunctionCall* tmpUME = Cast<UMaterialExpressionMaterialFunctionCall>(UME)) { SetMaterialFunctionTextureSampler(tmpUME, Type); }
				UME->MarkPackageDirty();
			}
		}
	}
}

void UDDToolsBPLibrary::SetMaterialFunctionTextureSampler(UMaterialExpressionMaterialFunctionCall* MEF, ESamplerSourceMode Type)
{
	if (MEF)
	{
		UMaterialFunction* UMF = Cast<UMaterialFunction>(MEF->MaterialFunction->GetBaseFunction());
		if (UMF)
		{
			
			for (UMaterialExpression* tmpUME : UMF->GetExpressions())
			{
				if (UMaterialExpressionTextureSample* tmpTMEA = Cast<UMaterialExpressionTextureSample>(tmpUME)) { tmpTMEA->SamplerSource = (Type); }
				if (UMaterialExpressionTextureSampleParameter* tmpUMEB = Cast<UMaterialExpressionTextureSampleParameter>(tmpUME)) { tmpUMEB->SamplerSource = (Type); }
				if (UMaterialExpressionMaterialFunctionCall* tmpUMEC = Cast<UMaterialExpressionMaterialFunctionCall>(tmpUME)) { SetMaterialFunctionTextureSampler(tmpUMEC, Type); }

			}
			UMF->MarkPackageDirty();
		}
	}
}

TArray<UObject*> UDDToolsBPLibrary::ListDir(FString DirPath, bool ListChildDir)
{
	TArray<UObject*> ret = TArray<UObject*>();
	FString ABSPath = FPaths::Combine(FPaths::ProjectContentDir(), DirPath.Replace(L"/Game/", L""));
	IFileManager& MyFileManager = IFileManager::Get();
	TArray<FString> AssetName;
	FString TmpPath;
	UObject* TmpObjcet;

	if (FPaths::DirectoryExists(*ABSPath))
	{
		//遍历子文件夹
		if (ListChildDir) { MyFileManager.FindFilesRecursive(AssetName, *ABSPath, L"*.uasset", true, false, true); }
		else { MyFileManager.FindFiles(AssetName, *ABSPath, true, false); }


		for (FString item : AssetName)
		{
			FString tmpItem = MyFileManager.ConvertToRelativePath(*item);
			tmpItem = tmpItem.Replace(*FPaths::ProjectContentDir(), L"/Game/");
			FString basenamne = FPaths::GetBaseFilename(*tmpItem);
			FString baseExtemsion = FPaths::GetExtension(*tmpItem);
			tmpItem = tmpItem.Replace(*FString(basenamne + *"." + baseExtemsion), *FString(basenamne + *"." + basenamne));
			//FString tmpItem = item.Replace(L".uasset",L"");
			//TmpPath = FPaths::Combine(*DirPath, FString(tmpItem+*"."+tmpItem));
			TmpObjcet = LoadObject<UObject>(nullptr, *tmpItem);
			if (TmpObjcet)
			{
				ret.Add(TmpObjcet);
				TmpObjcet = nullptr;
			}
		}
		return ret;
	}

	return TArray<UObject*>();
}

void UDDToolsBPLibrary::SetAssetDirct(UObject* Asset, bool& ret)
{
	if (Asset)
	{
		Asset->MarkPackageDirty();
		ret = true;
	}
	else { ret = false; }
}



void UDDToolsBPLibrary::RemoveStaticMeshLod(UStaticMesh* Mesh, int LodNum)
{
	const int IndexLod = Mesh->GetNumLODs();
	if (LodNum <= IndexLod)
	{
		Mesh->RemoveSourceModel(LodNum);
		Mesh->PostEditChange();
	}
	
	
}

void UDDToolsBPLibrary::RemoveStaticMeshAllLod(UStaticMesh* Mesh)
{
	if (FMessageDialog::Open(EAppMsgType::YesNo, FText::FromString(FString(L"警告！此操作将会移除所有lod，且不可回退！\n              确定移除吗？"))) == EAppReturnType::Yes)
	{
		int NumLods =0;
		while (1)
		{
			NumLods = Mesh->GetNumLODs();
			if (NumLods>1)
			{
				RemoveStaticMeshLod(Mesh, NumLods - 1);
				NumLods = Mesh->GetNumLODs();
			}	
			if (NumLods == 1) { Mesh->MarkPackageDirty(); break; }
		}
	}
}

void UDDToolsBPLibrary::AddStaticMeshLodNumTo8(UStaticMesh* Mesh)
{
	if (Mesh)
	{
		if (FMessageDialog::Open(EAppMsgType::YesNo, FText::FromString(FString(L"警告！此操作将会重新生成所有lod，且不可回退！\n              确定移除吗？"))) == EAppReturnType::Yes)
		{
			Mesh->SetNumSourceModels(8);
			Mesh->PostEditChange();
			Mesh->MarkPackageDirty();
		}
	}
}

PRAGMA_ENABLE_OPTIMIZATION

void UDDToolsBPLibrary::DDToolsTest(FString Message)
{
	FMessageDialog::Debugf(FText::FromString(Message));
}

FVector UDDToolsBPLibrary::GetVertexsCenter(TArray<FVector> Vertexs)
{
	const int ArrayLength = Vertexs.Num();
	float NumX = 0;
	float NumY = 0;
	float NumZ = 0;
	for (FVector3d item : Vertexs)
	{
		NumX += item.X;
		NumY += item.Y;
		NumZ += item.Z;
	}
	FVector ret = FVector(NumX / ArrayLength, NumY / ArrayLength, NumZ / ArrayLength);
	return ret;
}



bool UDDToolsBPLibrary::NewPackActor(UObject* InActor)
{
	
	if (InActor)
	{
		return true;
	}
	return false;
}

void UDDToolsBPLibrary::SelectFolder()
{
	TSharedPtr<SWindow> ParentWindow;
	if (FModuleManager::Get().IsModuleLoaded("MainFrame"))
	{
		IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
		ParentWindow = MainFrame.GetParentWindow();
	}

}

FString GetMountRelattivFormContent(FString Path) 
{
	if (Path.EndsWith("Contet")|| Path.EndsWith("Content\\")||Path.EndsWith("Conttent/")){return ""; }

	TArray<FString> TmpStrArray;
	Path.ParseIntoArray(TmpStrArray, TEXT("Content"));

	if (TmpStrArray.Num()==1){return ""; }

	FString TmpString = TmpStrArray[TmpStrArray.Num()-1];
	TmpString=TmpString.Replace(TEXT("\\"),TEXT("/"));
	if (TmpString.StartsWith("/"))
	{
		return TmpString;
	}
	return "/" + TmpString;

}

void UDDToolsBPLibrary::DDMountDir(FString Path)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (PlatformFile.DirectoryExists(*Path))
	{
		if (Path.Find("Content")>0)
		{
			FString PluginDir = FPaths::GetPath(FModuleManager::Get().GetModuleFilename("DDTools"));
			PluginDir = PluginDir.Replace(TEXT("Binaries/Win64"), TEXT(""));
			FString ConfigPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, "Config", "MountConfig.txt"));
			TArray<FString> MountList;
			bool ReadStat;
			ReadTextFileToArray(ConfigPath, ReadStat, MountList);
			/*如果该路径在历史记录中没找到，就挂载。*/
			if (MountList.Find(Path) < 0)
			{
				FString RelativePath=GetMountRelattivFormContent(Path);
				FString RootPath = "/Game" + RelativePath;
				if (RootPath=="/Game"||RootPath=="/Game/"||RootPath=="\\Game"||RootPath=="\\Game\\")
				{
					FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString(L"警告！\n该路径将会挂载到Content目录下。卸载时会导致整个Contetn被卸载！\n")+Path));
					UE_LOG(LogTemp,Error,TEXT("路径相对为Game路径，不允许被挂载！\"%s\""),*Path);
				}
				FPackageName::RegisterMountPoint(RootPath, *Path);
				MountList.Add(Path);
				WriteTextFileFormArray(ConfigPath, MountList, ReadStat);
			}
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("挂载路径不存在！\"%s\"."),*Path);
		}
	}
	

}
void UDDToolsBPLibrary::DDUnMountDir(FString Path)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.DirectoryExists(*Path))
	{
		FString PluginDir = FPaths::GetPath(FModuleManager::Get().GetModuleFilename("DDTools"));
		PluginDir = PluginDir.Replace(TEXT("Binaries/Win64"), TEXT(""));
		FString ConfigPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, "Config", "MountConfig.txt"));
		TArray<FString> MountList;
		bool ReadStat;
		ReadTextFileToArray(ConfigPath, ReadStat, MountList);
		if (MountList.Find(Path) >= 0)
		{
			FPackageName::UnRegisterMountPoint("/Game"+GetMountRelattivFormContent(Path), *Path);
			MountList.Remove(Path);
			WriteTextFileFormArray(ConfigPath, MountList, ReadStat);
		}


	}
}
void UDDToolsBPLibrary::ReadTextFileToArray(FString FilePath, bool& ret, TArray<FString>& OutLine)
{
	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file \"%s\"."), *FilePath);
		ret= false;
	}
	FileContent.ParseIntoArrayLines(OutLine);
	ret = true;
}
void UDDToolsBPLibrary::WriteTextFileFormArray(FString FilePath, TArray<FString> Line, bool& ret)
{
	FString FileContent = FString::Join(Line, TEXT("\n"));
	if (!FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to write file \"%s\"."), *FilePath);
		ret= false;
	}

	ret= true;
}
FString UDDToolsBPLibrary::GetDDToolsPath()
{
	FString PluginDir = FPaths::GetPath(FModuleManager::Get().GetModuleFilename("DDTools"));
	PluginDir = PluginDir.Replace(TEXT("Binaries/Win64"), TEXT(""));
	return PluginDir;
}
#pragma optimize("", on)
