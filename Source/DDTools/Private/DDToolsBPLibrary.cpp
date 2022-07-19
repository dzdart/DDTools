// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDToolsBPLibrary.h"
#include "DDTools.h"
#include "HAL/IPlatformFileModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

UDDToolsBPLibrary::UDDToolsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}



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
			for (UMaterialExpression* UME : mat->Expressions)
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
			for (UMaterialExpression* tmpUME : UMF->FunctionExpressions)
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

bool UDDToolsBPLibrary::LoadPngToDyT2d(const FString& ImagePath, UTexture2DDynamic* InDyTexture, float& Width, float Height)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*ImagePath)) { return false; }

	TArray<uint8> ImageResultData;
	FFileHelper::LoadFileToArray(ImageResultData, *ImagePath);
	FString Ex = FPaths::GetExtension(ImagePath, false);

	//图片加载模块
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");
	TSharedPtr<IImageWrapper> ImageWrapperPtr = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	if (ImageWrapperPtr.IsValid() && ImageWrapperPtr->SetCompressed(ImageResultData.GetData(), ImageResultData.GetAllocatedSize()))
	{
		TArray<uint8>* OutData = new TArray<uint8>();//跟格式无关的颜色数据

		ImageWrapperPtr->GetRaw(ERGBFormat::RGBA, 8, *OutData);

		InDyTexture = UTexture2DDynamic::Create(ImageWrapperPtr->GetWidth(), ImageWrapperPtr->GetHeight());

		if (InDyTexture)
		{
			InDyTexture->SRGB = true;
			InDyTexture->UpdateResource();

			FTexture2DDynamicResource* Texture2DDyRes = static_cast<FTexture2DDynamicResource*>(InDyTexture->Resource);
			FRHITexture2D* RHITexture2D = Texture2DDyRes->GetTexture2DRHI();
			int64 w = RHITexture2D->GetSizeX();
			int64 h = RHITexture2D->GetSizeY();
			uint32 DestStride = 0;
			uint8* DestData = reinterpret_cast<uint8*>(RHILockTexture2D(RHITexture2D, 0, EResourceLockMode::RLM_WriteOnly, DestStride, false));

			for (int64 y = 0; y < Height; ++y)
			{
				int64 DestPtrStride = y * DestStride;
				uint8* DestPtr = &DestData[DestStride];

				uint8* StrData = OutData->GetData();
				int64 SrcPtrStride = y * Width;


				const FColor* SrcPtr = &((FColor*)(StrData))[SrcPtrStride];

				for (int64 x = 0; x < Width; ++x)
				{
					*DestPtr++ = SrcPtr->B;
					*DestPtr++ = SrcPtr->G;
					*DestPtr++ = SrcPtr->R;
					*DestPtr++ = SrcPtr->A;
					SrcPtr++;

				}
			}

			RHIUnlockTexture2D(RHITexture2D, 0, false, false);

		}
		delete OutData;
		OutData = nullptr;
	}



	return true;
}

PRAGMA_DISABLE_OPTIMIZATION
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

