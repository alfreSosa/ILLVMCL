// Fill out your copyright notice in the Description page of Project Settings.
#include "ILLMVSquareGrid.h"
#include "DrawDebugHelpers.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVSquareGrid::GenerateGrid()
{
    // Invalidate previous grid
    m_Grid.Empty();

    // Considering actor location as the corner of the grid
    const FVector gridCornerOrigin = GetActorLocation();
    const FVector tileCenterOffset = FVector(TileSize * 0.5f, TileSize * 0.5f, 0.0f);
    const FVector firstTileOrigin = gridCornerOrigin + tileCenterOffset;

    for (int32 i = 0; i < Columns; ++i)
    {
        FUILLVMTilesColumn column;
        for (int32 j = 0; j < Rows; ++j)
        {
            FUILLVMTile tile;
            tile.WorldLocation = FVector(firstTileOrigin.X + TileSize * j, firstTileOrigin.Y + TileSize * i, firstTileOrigin.Z);
            column.TilesRow.Add(tile);
        }
        m_Grid.Add(column);
    }

    DrawDebugGrid();
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVSquareGrid::DrawDebugGrid()
{
    for (int32 i = 0; i < Columns; ++i)
    {
        for (int32 j = 0; j < Rows; ++j)
        {
           DrawDebugBox(GetWorld(), m_Grid[i].TilesRow[j].WorldLocation, FVector(TileSize), FQuat::Identity, FColor::Blue, false, 10.0f,0, 1.0f);
        }
    }
}
