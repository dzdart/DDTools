// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Classes/Materials/Material.h"
#include "Engine/Classes/Materials/MaterialExpression.h"
#include "Engine/Classes/Materials/MaterialExpressionScalarParameter.h"
#include "Engine/Classes/Engine/Texture2DDynamic.h"
#include "Runtime/Core/Public/Misc/MessageDialog.h"
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

	/*����ȫ����ط���*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "���ò��ʱ�������", ToolTips = "���ò��ʱ�������", Keywords = "SetMaterialParameterName"), Category = "BlueprintExpansionPack|Material")
	static void SetMaterialParameterName(UMaterialExpressionScalarParameter* ME, FName Name, FName Group);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "���ò��ʹ�׷��Ӱ����", ToolTips = "���ò������Ͷ���׷��Ӱ����", Keywords = "SetMatRayShadow"), Category = "BlueprintExpansionPack|Material")
	static UMaterial* SetMatRayShadow(UMaterial* Mat, bool on);

	//���ò���������Tex�ڵ��SamplerType
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "���ò�������ͼɨ����SamplerType", ToolTips = "���ò�������ͼɨ����SamplerType", Keywords = "SetMaterialTextureSampler"), Category = "BlueprintExpansionPack|Material")
	static void SetMaterialTextureSampler(TArray<UObject*> Objects, ESamplerSourceMode Type);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "���ò��ʺ�����ͼɨ����SamplerType", ToolTips = "���ò��ʺ�����ͼɨ����SamplerType", Keywords = "SetMaterialFunctionTextureSampler"), Category = "BlueprintExpansionPack|Material")
	static void SetMaterialFunctionTextureSampler(UMaterialExpressionMaterialFunctionCall* MEF, ESamplerSourceMode Type);

	/*ContentFile*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "�г����ж���", ToolTips = "��ȡ�ļ���������UE����ΪUObject", Keywords = "ListDir"), Category = "BlueprintExpansionPack|File")
	static TArray<UObject*> ListDir(FString DirPath, bool ListChildDir);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "���ļ����Ϊδ����״̬", ToolTips = "���ļ����Ϊδ����״̬", Keywords = "MarkDirty"), Category = "BlueprintExpansionPack|File")
	static void SetAssetDirct(UObject* Asset, bool& ret);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "��ȡ�ļ�����̬��ͼ", ToolTips = "�ӱ���Ӳ�̶�ȡpng�ļ�����̬��ͼ", Keywords = "LoadPNGToTexture2DDynamic"), Category = "BlueprintExpansionPack|File")
	static bool LoadPngToDyT2d(const FString& ImagePath, UTexture2DDynamic* InDyTexture, float& Width, float Height);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveStaticMeshLod", ToolTips = "�Ƴ���̬������ָ��LOD", Keywords = "RemoveStaticMeshLod"), Category = "DDToolsTest")
	static void RemoveStaticMeshLod(UStaticMesh* Mesh,int LodNum);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveStaticMeshAllLod", ToolTips = "�Ƴ���̬������ָ��LOD", Keywords = "RemoveStaticMeshLod"), Category = "DDToolsTest")
	static void RemoveStaticMeshAllLod(UStaticMesh* Mesh);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddStaticMeshLodNumTo8", ToolTips = "����ģ��lod������8", Keywords = "RemoveStaticMeshLod"), Category = "DDToolsTest")
	static void AddStaticMeshLodNumTo8(UStaticMesh* Mesh);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DDToolsTest", ToolTips = "DDToolsTest", Keywords = "LoadPNGToTexture2DDynamic"), Category = "DDToolsTest")
	static void DDToolsTest(FString Message);

};

