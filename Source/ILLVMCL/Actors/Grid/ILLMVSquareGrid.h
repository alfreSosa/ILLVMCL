// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ILLVMGrid.h"
#include "ILLMVSquareGrid.generated.h"

/**
* Square grid.
*/
UCLASS()
class ILLVMCL_API AILLMVSquareGrid : public AILLVMGrid
{
	GENERATED_BODY()
	
public:
    /** Squareshape:Width = TileSize. Height = TileSize */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0, ClampMax = 1000, UIMax = 1000), Category = "ILLVM|Grid|Square")
    int32 TileSize = 100;

public:	

#pragma region AILLVMGrid
    /** Overridden to generate grid with squares*/
    virtual void GenerateGrid() override;

    /** Overridden to draw debug grid with squares*/
    virtual void DrawDebugGrid() override;

    virtual TArray<FVector2D> GetPointNeighbours(const FVector2D& Origin) const override;
    virtual FVector2D GetClosestNeighbourToPoint(const FVector2D& Origin, const FVector2D& Destiny) const override;
#pragma endregion

};
