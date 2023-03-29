// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Classes/Materials/Material.h"
#include "Engine/Classes/Materials/MaterialExpression.h"
#include "Engine/Classes/Materials/MaterialExpressionScalarParameter.h"
#include "Engine/Classes/Engine/Texture2DDynamic.h"
#include "Runtime/Core/Public/Misc/MessageDialog.h"
#include "Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/CoreUObject/Public/Misc/PackageName.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "AssetRegistryModule.h"
#include "Engine/Classes/Engine/ObjectLibrary.h"
#include "DDToolsBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UDDToolsBPLibrary : public UBlueprintFunctionLibrary
{
public:

	GENERATED_UCLASS_BODY()


	/*材质全球相关方法*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "设置材质变量名称", ToolTips = "设置材质变量名称", Keywords = "SetMaterialParameterName"), Category = "BlueprintExpansionPack|Material")
	static void SetMaterialParameterName(UMaterialExpressionScalarParameter* ME, FName Name, FName Group);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "设置材质光追阴影开关", ToolTips = "设置材质球的投射光追阴影开关", Keywords = "SetMatRayShadow"), Category = "BlueprintExpansionPack|Material")
	static UMaterial* SetMatRayShadow(UMaterial* Mat, bool on);

	//设置材质球所有Tex节点的SamplerType
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "设置材质球贴图扫描器SamplerType", ToolTips = "设置材质球贴图扫描器SamplerType", Keywords = "SetMaterialTextureSampler"), Category = "BlueprintExpansionPack|Material")
	static void SetMaterialTextureSampler(TArray<UObject*> Objects, ESamplerSourceMode Type);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "设置材质函数贴图扫描器SamplerType", ToolTips = "设置材质函数贴图扫描器SamplerType", Keywords = "SetMaterialFunctionTextureSampler"), Category = "BlueprintExpansionPack|Material")
	static void SetMaterialFunctionTextureSampler(UMaterialExpressionMaterialFunctionCall* MEF, ESamplerSourceMode Type);

	/*ContentFile*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "列出所有对象", ToolTips = "读取文件夹下所有UE对象为UObject", Keywords = "ListDir"), Category = "BlueprintExpansionPack|File")
	static TArray<UObject*> ListDir(FString DirPath, bool ListChildDir);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "将文件标记为未保存状态", ToolTips = "将文件标记为未保存状态", Keywords = "MarkDirty"), Category = "BlueprintExpansionPack|File")
	static void SetAssetDirct(UObject* Asset, bool& ret);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "获取文件夹下指定类的所有AssetData", ToolTips = "获取文件夹下指定类的所有AssetData", Keywords = "GetAllAssetDataOfClass"), Category = "BlueprintExpansionPack|File")
	static TArray<FAssetData> GetAllAssetDataOfClass(UClass* Class,FString Path);

	/*UFUNCTION(BlueprintCallable, meta = (DisplayName = "读取文件到动态贴图", ToolTips = "从本地硬盘读取png文件到动态贴图", Keywords = "LoadPNGToTexture2DDynamic"), Category = "BlueprintExpansionPack|File")
	static bool LoadPngToDyT2d(const FString& ImagePath, UTexture2DDynamic* InDyTexture, float& Width, float Height);*/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveStaticMeshLod", ToolTips = "移除静态网格体指定LOD", Keywords = "RemoveStaticMeshLod"), Category = "BlueprintExpansionPack|StaticMesh")
	static void RemoveStaticMeshLod(UStaticMesh* Mesh,int LodNum);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveStaticMeshAllLod", ToolTips = "移除静态网格体指定LOD", Keywords = "RemoveStaticMeshLod"), Category = "BlueprintExpansionPack|StaticMesh")
	static void RemoveStaticMeshAllLod(UStaticMesh* Mesh);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddStaticMeshLodNumTo8", ToolTips = "增加模型lod数量至8", Keywords = "RemoveStaticMeshLod"), Category = "BlueprintExpansionPack|StaticMesh")
	static void AddStaticMeshLodNumTo8(UStaticMesh* Mesh);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DDToolsTest", ToolTips = "DDToolsTest", Keywords = "LoadPNGToTexture2DDynamic"), Category = "BlueprintExpansionPack|StaticMesh")
	static void DDToolsTest(FString Message);

	/*OtherFunction*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetVertexsCenter", ToolTips = "获取N个顶点坐标的中心点", Keywords = "GetVertexsCenter"), Category = "BlueprintExpansionPack|Math")
	static FVector GetVertexsCenter(TArray<FVector> Vertexs);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsPowerOfTwo", ToolTips = "判断整型是否2的幂次方", Keywords = "IsPowerOfTwo"), Category = "BlueprintExpansionPack|Math")
		static bool IsPowerOfTwo(int n);
	

	/*Dialog Function*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SelectFolder", ToolTips = "SelectFolder", Keywords = "SelectFolder"), Category = "DDToolsTest")
	static void SelectFolder();

	/*MountFunction*/
	static FString GetMountRelattivFormContent(FString Path);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MountDir", Keywords = "MountDirs,"), Category = "DDToolsTest")
	static void DDMountDir(FString Path);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UnMountDir", Keywords = "UnMountDirs,"), Category = "DDToolsTest")
	static void DDUnMountDir(FString Path);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ReadTextFileToArray", Keywords = "ReadTextFileToArray,"), Category = "DDToolsTest")

		/*Txt Write and read*/
	static void ReadTextFileToArray(FString FilePath,bool& ret,TArray<FString>& OutLine);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WriteTextFileFormArray", Keywords = "WriteTextFileFormArray,"), Category = "DDToolsTest")
	static void WriteTextFileFormArray(FString FilePath,TArray<FString> Line,bool& ret);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetDDToolsPath", Keywords = "GetDDToolsPath,"), Category = "DDToolsTest")


	static FString GetDDToolsPath();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CMD", Keywords = "CMD"), Category = "DDToolsTest")
		static void RunCmd(FString Command);

};

