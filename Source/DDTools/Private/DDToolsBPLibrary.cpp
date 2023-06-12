// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDToolsBPLibrary.h"
#include "DDTools.h"
#include "HAL/IPlatformFileModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "MainFrame/Public/Interfaces/IMainFrameModule.h"
typedef float(*_getCircleArea)(float radius);
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

void UDDToolsBPLibrary::SaveAssets(TArray<FAssetData> AssetData, TArray<UObject*> Objects)
{
	TArray<UPackage*> ToSavePackage;
	TArray<FAssetData> ObjectAssetData;
	for (UObject* item:Objects)
	{
		ToSavePackage.Add(item->GetPackage());
	}
	for (FAssetData item:AssetData)
	{
		ToSavePackage.Add(item.GetPackage());
	}
	UEditorLoadingAndSavingUtils::SavePackages(ToSavePackage,false);
}

void UDDToolsBPLibrary::SetMaterialToVT(UMaterial* Mat)
{
	if (Mat)
	{
		TConstArrayView<TObjectPtr<UMaterialExpression>> Expressions=Mat->GetExpressions();
		for (auto item : Expressions)
		{
			if (UMaterialExpressionTextureBase* MatExpressionTextureBase=Cast<UMaterialExpressionTextureBase>(item))
			{
				MatExpressionTextureBase->SamplerType;
			}
		}
	}
}



void UDDToolsBPLibrary::SetTextureUseVt(UTexture* Tex, bool UseVt, bool MarkDirt)
{
	if (Tex)
	{
		FString EnumValueString = FindObject<UEnum>(ANY_PACKAGE, TEXT("TextureCompressionSettings"), true)->GetNameStringByValue(Tex->CompressionSettings);
		if (EnumValueString.Find("HDR")<0|| FMath::IsPowerOfTwo(Tex->Source.GetSizeX()) || FMath::IsPowerOfTwo(Tex->Source.GetSizeY()))
		{
			Tex->VirtualTextureStreaming = UseVt;
			if (MarkDirt)
			{
				Tex->PostEditChange();
				Tex->MarkPackageDirty();
			}
		}
	}
}

void UDDToolsBPLibrary::ResetTextureSize(UTexture2D* Tex, int NewX, int NewY)
{
	if (Tex && NewX > 0 && NewY > 0)
	{
		UTextureRenderTarget2D* NewRenderTarget2D = NewObject<UTextureRenderTarget2D>();
		if (!NewRenderTarget2D){return;}
		NewRenderTarget2D->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;
		NewRenderTarget2D->ClearColor = FLinearColor::Black;
		NewRenderTarget2D->bAutoGenerateMips = true;
		NewRenderTarget2D->InitAutoFormat(NewX, NewY);
		NewRenderTarget2D->UpdateResourceImmediate(true);

		UMaterial* Parent = LoadObject<UMaterial>(nullptr,TEXT("/Script/Engine.Material'/DDTools/UtilitMaterial/RenderTargetMat.RenderTargetMat'"));
		if (!Parent) { return; };
		UMaterialInstanceDynamic* NewMId = UMaterialInstanceDynamic::Create(Parent, nullptr);
		if (!NewMId) { return; }
		NewMId->SetTextureParameterValue(FName("Tex"),Tex);
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(nullptr, NewRenderTarget2D, NewMId);
		UKismetRenderingLibrary::ConvertRenderTargetToTexture2DEditorOnly(nullptr,NewRenderTarget2D, Tex);
		UKismetRenderingLibrary::ReleaseRenderTarget2D(NewRenderTarget2D);
		Parent = nullptr;
		NewMId = nullptr;
	}
}

EMaterialSamplerType UDDToolsBPLibrary::FlipVirtualSampleOrNormal(EMaterialSamplerType InType)
{
	TMap<EMaterialSamplerType, EMaterialSamplerType> data = {
		{SAMPLERTYPE_Color,SAMPLERTYPE_VirtualColor},
		{SAMPLERTYPE_Grayscale,SAMPLERTYPE_VirtualGrayscale},
		{SAMPLERTYPE_Alpha,SAMPLERTYPE_VirtualAlpha},
		{SAMPLERTYPE_Normal,SAMPLERTYPE_VirtualNormal},
		{SAMPLERTYPE_Masks,SAMPLERTYPE_VirtualMasks},
		{SAMPLERTYPE_LinearColor,SAMPLERTYPE_VirtualLinearColor},
		{SAMPLERTYPE_LinearGrayscale,SAMPLERTYPE_VirtualLinearGrayscale},

		{SAMPLERTYPE_VirtualColor,SAMPLERTYPE_Color},
		{SAMPLERTYPE_VirtualGrayscale,SAMPLERTYPE_Grayscale},
		{SAMPLERTYPE_VirtualAlpha,SAMPLERTYPE_Alpha},
		{SAMPLERTYPE_VirtualNormal,SAMPLERTYPE_Normal},
		{SAMPLERTYPE_VirtualMasks,SAMPLERTYPE_Masks},
		{SAMPLERTYPE_VirtualLinearColor,SAMPLERTYPE_LinearColor},
		{SAMPLERTYPE_VirtualLinearGrayscale,SAMPLERTYPE_LinearGrayscale},

	};
	if (data.Contains(InType))
	{
		return *data.Find(InType);
	}
	return InType;
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

TArray<FAssetData> UDDToolsBPLibrary::GetAllAssetDataOfClass(UClass* Class, FString Path)
{
	UObjectLibrary* objectLibrary = UObjectLibrary::CreateLibrary(Class,false,GIsEditor);
	if (objectLibrary) 
	{
		objectLibrary->AddToRoot();
	}
	objectLibrary->LoadAssetDataFromPath(Path);
	TArray<FAssetData> ret;
	objectLibrary->GetAssetDataList(ret);
	return ret;
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

bool UDDToolsBPLibrary::IsPowerOfTwo(int n)
{

	return FMath::IsPowerOfTwo(n);
}

UObject* UDDToolsBPLibrary::CreateAssetFormClass(FString Dir, FString AssetName, TSubclassOf<UObject> ObjectClass)
{
	if (Dir.StartsWith("/Game"))
	{
		UPackage* package = CreatePackage(*AssetName);
		
		UObject* object = NewObject<UObject>(package,ObjectClass,*AssetName,EObjectFlags::RF_Public|EObjectFlags::RF_Standalone|EObjectFlags::RF_HasExternalPackage|EObjectFlags::RF_ArchetypeObject);
		object->SetExternalPackage(package);
		object->MarkPackageDirty();
		FAssetRegistryModule::AssetCreated(object);
		return object;
	}
	return nullptr;
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

FString UDDToolsBPLibrary::GetMountRelattivFormContent(FString Path)
{
	if (Path.EndsWith("Contet") || Path.EndsWith("Content\\") || Path.EndsWith("Conttent/")) { return ""; }

	TArray<FString> TmpStrArray;
	Path.ParseIntoArray(TmpStrArray, TEXT("Content"));

	if (TmpStrArray.Num() == 1) { return ""; }

	FString TmpString = TmpStrArray[TmpStrArray.Num() - 1];
	TmpString = TmpString.Replace(TEXT("\\"), TEXT("/"));
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
			FString ConfigPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectConfigDir(), "MountConfig.txt"));
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
		FString ConfigPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectConfigDir(), "MountConfig.txt"));
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
	return FPaths::ConvertRelativePathToFull(PluginDir);
}
void UDDToolsBPLibrary::RunCmd(FString Command)
{
	TArray<FString> CommandList;
	Command.ParseIntoArray(CommandList,TEXT(" "));

	FString CommandHead = CommandList[0];
	FString Parms = Command.Replace(*FString(CommandHead + " "), TEXT(""));



	FProcHandle currHandle = FPlatformProcess::CreateProc(*CommandHead, *Parms, true, false, false, nullptr, 0, nullptr, nullptr);
	UE_LOG(LogTemp, Warning, TEXT("URL:::%s"), *Command);
}
#pragma optimize("", on)
