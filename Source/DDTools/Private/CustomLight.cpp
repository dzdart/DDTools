// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLight.h"
#include "UObject/NoExportTypes.h"

#pragma optimize("", off)
// Sets default values
ACustomLight::ACustomLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("RootLight"));
	RootLight->bAffectsWorld = false;
	this->SetRootComponent(RootLight);

	RLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("RLight"));
	Lights.Add(RLight);
	RLight->SetLightColor(FLinearColor(1,0,0));
	GLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("GLight"));
	Lights.Add(GLight);
	GLight->SetLightColor(FLinearColor(0,1,0));
	BLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("BLight"));
	Lights.Add(BLight);
	BLight->SetLightColor(FLinearColor(0, 0, 1));

	for (USpotLightComponent* item :Lights)
	{
		item->SetupAttachment(this->GetRootComponent());
		item->SetCastShadows(false);
		item->StaticEditorTexture = nullptr;
		item->DynamicEditorTexture = nullptr;
	}
}

// Called when the game starts or when spawned
void ACustomLight::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomLight::CreateMaterialFunction()
{
	if (!ParentMaterialFunction&&!Tex){return;}
	if (RLight)
	{
		if (!RMaterial)
		{
			RMaterial = UMaterialInstanceDynamic::Create(ParentMaterialFunction, nullptr);
		}
		RMaterial->SetTextureParameterValue(TEXT("Tex"), Tex);
		RMaterial->SetVectorParameterValue(TEXT("Channel"),FVector(1,0,0));
		RLight->SetLightFunctionMaterial(RMaterial);
	}

	if (GLight)
	{
		if (!GMaterial)
		{
			GMaterial = UMaterialInstanceDynamic::Create(ParentMaterialFunction, nullptr);
		}
		GMaterial->SetTextureParameterValue(TEXT("Tex"), Tex);
		GMaterial->SetVectorParameterValue(TEXT("Channel"), FVector(0, 1, 0));
		GLight->SetLightFunctionMaterial(GMaterial);
	}

	if (BLight)
	{
		if (!BMaterial)
		{
			BMaterial = UMaterialInstanceDynamic::Create(ParentMaterialFunction, nullptr);
		}
		BMaterial->SetTextureParameterValue(TEXT("Tex"), Tex);
		BMaterial->SetVectorParameterValue(TEXT("Channel"), FVector(0, 0, 1));
		BLight->SetLightFunctionMaterial(BMaterial);
	}
}
FColor CxC(FColor A,FColor B) 
{
	float a = A.R / 255;
	float b = A.G / 255;
	float c = A.B / 255;
	uint8 Rr = static_cast<uint8>(a * B.R);
	uint8 Rg = static_cast<uint8>(b * B.G);
	uint8 Rb = static_cast<uint8>(c * B.B);
	return FColor(Rr, Rg, Rb, 1);


}
void ACustomLight::CopyParam()
{
	/*将RootLight的属性复制大RGBLinght上*/
	if (RootLight)
	{

		for (USpotLightComponent* item:Lights)
		{
			if (item)
			{
				item->Intensity = RootLight->Intensity / 3;
				//item->LightColor = CxC(RootLight->LightColor, item->LightColor);
				item->AttenuationRadius = RootLight->AttenuationRadius;
				item->InnerConeAngle = RootLight->InnerConeAngle;
				item->OuterConeAngle = RootLight->OuterConeAngle;
				item->SourceRadius = RootLight->SourceRadius;
				item->SourceLength = RootLight->SourceLength;
				item->bUseTemperature = RootLight->bUseTemperature;
				item->Temperature = RootLight->Temperature;

				/*这两个值有自己的特殊属性*/
				//item->bAffectsWorld = RootLight->bAffectsWorld;
				//item->CastShadows = RootLight->CastShadows;

				item->IndirectLightingIntensity = RootLight->IndirectLightingIntensity;
				item->VolumetricScatteringIntensity = RootLight->VolumetricScatteringIntensity;
				item->IntensityUnits = RootLight->IntensityUnits;
				item->bUseInverseSquaredFalloff = RootLight->bUseInverseSquaredFalloff;
				item->LightFalloffExponent = RootLight->LightFalloffExponent;
				item->InverseExposureBlend = RootLight->InverseExposureBlend;
				item->SpecularScale = RootLight->SpecularScale;
				item->ShadowResolutionScale = RootLight->ShadowResolutionScale;
				item->ShadowBias = RootLight->ShadowBias;
				item->ShadowSlopeBias = RootLight->ShadowSlopeBias;
				item->ShadowSharpen = RootLight->ShadowSharpen;
				item->ContactShadowLength = RootLight->ContactShadowLength;
				item->ContactShadowLengthInWS = RootLight->ContactShadowLengthInWS;
				item->ContactShadowCastingIntensity = RootLight->ContactShadowCastingIntensity;
				item->ContactShadowNonCastingIntensity = RootLight->ContactShadowNonCastingIntensity;
				item->CastTranslucentShadows = RootLight->CastTranslucentShadows;
				item->bCastShadowsFromCinematicObjectsOnly = RootLight->bCastShadowsFromCinematicObjectsOnly;
				item->bAffectDynamicIndirectLighting = RootLight->bAffectDynamicIndirectLighting;
				item->bForceCachedShadowsForMovablePrimitives = RootLight->bForceCachedShadowsForMovablePrimitives;
				item->LightingChannels = RootLight->LightingChannels;
				item->CastStaticShadows = RootLight->CastStaticShadows;
				item->CastDynamicShadows = RootLight->CastDynamicShadows;
				item->bAffectTranslucentLighting = RootLight->bAffectTranslucentLighting;
				item->bTransmission = RootLight->bTransmission;
				item->bCastVolumetricShadow = RootLight->bCastVolumetricShadow;
				item->bCastDeepShadow = RootLight->bCastDeepShadow;
				item->CastRaytracedShadow = RootLight->CastRaytracedShadow;
				item->bAffectReflection = RootLight->bAffectReflection;
				item->bAffectGlobalIllumination = RootLight->bAffectGlobalIllumination;
				item->DeepShadowLayerDistribution = RootLight->DeepShadowLayerDistribution;
			}
		}
	}
	
}

// Called every frame
void ACustomLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomLight::OnConstruction(const FTransform& Transform)
{
	CopyParam();
	if (Tex)
	{
		CreateMaterialFunction();
	}
}

#pragma optimize("", on)