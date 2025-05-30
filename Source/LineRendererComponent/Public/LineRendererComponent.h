// Copyright 2023 Petr Leontev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Materials/MaterialRelevance.h"
#include "Templates/SharedPointer.h"
#include "LineSectionInfo.h"
#include "LineRendererComponent.generated.h"

class UMaterialInstanceDynamic;
class UMaterialInterface;
class FPrimitiveSceneProxy;
class FLineRendererComponentSceneProxy;


UCLASS(hidecategories = (Object, LOD), meta = (BlueprintSpawnableComponent))
class LINERENDERERCOMPONENT_API ULineRendererComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	ULineRendererComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void CreateLine2Points(int32 SectionIndex, const FVector& StartPoint, const FVector& EndPoint, const FLinearColor& Color, float Thickness = 1.0f, int32 NumSegments = 1, bool bScreenSpace = false);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void CreateLine(int32 SectionIndex, const TArray<FVector>& Vertices, const FLinearColor& Color, float Thickness = 1.0f, bool bScreenSpace = false);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void RemoveLine(int32 SectionIndex);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void RemoveAllLines();

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	void SetLineVisible(int32 SectionIndex, bool bNewVisibility);

	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	bool IsLineVisible(int32 SectionIndex) const;

	/** Returns number of lines currently created for this component */
	UFUNCTION(BlueprintCallable, Category = "Components|LineRenderer")
	int32 GetNumSections() const;

protected:
	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	//~ End UPrimitiveComponent Interface.

	//~ Begin UMeshComponent Interface.
	virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;
	virtual FMaterialRelevance GetMaterialRelevance(ERHIFeatureLevel::Type InFeatureLevel) const override;

	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;
	//~ End UMeshComponent Interface.

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	UMaterialInterface* LineMaterial;

private: 
	UMaterialInterface* CreateOrUpdateMaterial(int32 SectionIndex, const FLinearColor& Color);

	//~ Begin USceneComponent Interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	virtual void UpdateBounds() override;
	//~ Begin USceneComponent Interface.

private:
	UPROPERTY(Transient)
    TMap<int32, FLineSectionInfo> Sections;

	UPROPERTY(Transient)
    TMap<int32, UMaterialInstanceDynamic*> SectionMaterials;

    friend class FLineRendererComponentSceneProxy;
};


