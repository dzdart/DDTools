// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SpotLightComponent.h"
#include "Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectAllocator.h"


#include "CustomLight.generated.h"

UCLASS()
class DDTOOLS_API ACustomLight : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "默认")
	TObjectPtr<USpotLightComponent> RootLight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Light")
	UTexture2D* Tex;
private:
	/** Please add a variable description */

	TArray<USpotLightComponent*> Lights;

	USpotLightComponent* RLight;
	USpotLightComponent* GLight;
	USpotLightComponent* BLight;

	/*MaterialFunction*/
	UMaterialInterface* ParentMaterialFunction = LoadObject<UMaterialInterface>(this, TEXT("/Script/Engine.Material'/DDTools/MaterialFunction/ColorLightFunction.ColorLightFunction'"));
	UMaterialInstanceDynamic* RMaterial;
	UMaterialInstanceDynamic* GMaterial;
	UMaterialInstanceDynamic* BMaterial;
public:	
	// Sets default values for this actor's properties
	ACustomLight();
	/** Please add a function description */
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CreateMaterialFunction();
	void CopyParam();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

};
