// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ILLVMGrid.generated.h"

/** 
*	Base struct to represent a logical tile
*	Defined to contains data related to the grid but not any visual representation.
*/
USTRUCT()
struct FUILLVMTile 
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FVector WorldLocation;
};

/**
*	Rows per column
*	Struct to have a bi dimensional array of tiles using TArray.
*	To simplify calculation and operations.
*/
USTRUCT()
struct FUILLVMTilesColumn
{
    GENERATED_BODY()

public:
	/** Tiles per row*/
	UPROPERTY()
	TArray<FUILLVMTile> TilesRow;
};

/** 
* Base class to define the common properties and interface for grids
* Any type of grid (square, hexagonal, etc) should inherit from this class.
*/
UCLASS()
class ILLVMCL_API AILLVMGrid : public AActor
{
	GENERATED_BODY()
	
public:
	/** Grid's number of rows */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0, ClampMax = 1000, UIMax = 1000), Category = "ILLVM|Grid")
	int32 Rows = 100;

    /** Grid's number of columns */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0, ClampMax = 1000, UIMax = 1000), Category = "ILLVM|Grid")
    int32 Columns = 100;

public:	

	/** Default Constructor*/
	AILLVMGrid(const FObjectInitializer& ObjectInitializer);

#pragma region AActor

	/** Overridden to genarate the grid when the actor is placed in the world*/
    virtual void OnConstruction(const FTransform& Transform) override;
#pragma endregion

	/**
	*	AILLVMGrid::GenerateGrid - virtual public 
	*	@brief - Method called on actor construction to generate the grid. Child classes must implement it and fill the grid as desired.
	*	@return void
	*/
	virtual void GenerateGrid() { }

	/**
	*	AILLVMGrid::GetGrid - public 
	*	@return const TArray<UILLVMTilesColumn> -  Read only getter of the grid
	*/
	const TArray<FUILLVMTilesColumn>& GetGrid() const { return m_Grid; }

	/**
	*	AILLVMGrid::DrawDebugGrid - virtual public 
    *	@brief - Empty method where child classes should write code about debug draw
    *	@return void
	*/
	virtual void DrawDebugGrid() { }

	FVector2D GetGridRandomLocation() const;

	const FVector& GetGridWorldLocation(const FVector2D& GridLocation) const;

protected:
#pragma region AActor

    /** Overridden to register grid in the simulation subsystem*/
    virtual void BeginPlay() override;

#pragma endregion
protected:

	/** Grid representation. Assumming bidimensional grid*/
	UPROPERTY()
	TArray<FUILLVMTilesColumn> m_Grid;
};
