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
    const FVector gridCornerOrigin = GetActorLocation() + FVector(TileSize * 0.5f, TileSize * 0.5f, 0.0f);
   
 
    for (int32 i = 0; i < Columns; ++i)
    {
        FUILLVMTilesColumn column;
        for (int32 j = 0; j < Rows; ++j)
        {
            FUILLVMTile tile;
            tile.WorldLocation = FVector(gridCornerOrigin.X + TileSize * j, gridCornerOrigin.Y + TileSize * i, gridCornerOrigin.Z);
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
           DrawDebugPoint(GetWorld(), m_Grid[i].TilesRow[j].WorldLocation, 5.0f, FColor::Red, true, 10.0f);
           DrawDebugBox(GetWorld(), m_Grid[i].TilesRow[j].WorldLocation, FVector(TileSize * 0.5f), FQuat::Identity, FColor::Blue, true, 10.0f,0, 1.0f);
        }
    }
}
