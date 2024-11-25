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

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

TArray<FVector2D> AILLMVSquareGrid::GetPointNeighbours(const FVector2D& Origin) const
{
    TArray<FVector2D> neighbours;
 
    // East
    if ((Origin.X + 1) < Columns)
    {
        neighbours.Add(FVector2D(Origin.X + 1, Origin.Y));
    }

    // NorthEast
    if ((Origin.X + 1) < Columns && (Origin.Y - 1) >= 0)
    {
        neighbours.Add(FVector2D(Origin.X + 1, Origin.Y - 1));
    }

    // SouthEast
    if ((Origin.X + 1) < Columns && (Origin.Y + 1) < Rows)
    {
        neighbours.Add(FVector2D(Origin.X + 1, Origin.Y + 1));
    }

    // West
    if ((Origin.X - 1) >= 0)
    {
        neighbours.Add(FVector2D(Origin.X - 1, Origin.Y));
    }

    // NorthWest
    if ((Origin.X - 1) >= 0 && (Origin.Y - 1) >= 0)
    {
        neighbours.Add(FVector2D(Origin.X - 1, Origin.Y - 1));
    }

    // SouthWest
    if ((Origin.X - 1) >= 0 && (Origin.Y + 1) < Rows)
    {
        neighbours.Add(FVector2D(Origin.X - 1, Origin.Y + 1));
    }

    // North
    if ((Origin.Y - 1) >= 0)
    {
        neighbours.Add(FVector2D(Origin.X, Origin.Y - 1));
    }

    // South
    if ((Origin.Y + 1) < Rows)
    {
        neighbours.Add(FVector2D(Origin.X, Origin.Y + 1));
    }

    return neighbours;
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

FVector2D AILLMVSquareGrid::GetClosestNeighbourToPoint(const FVector2D& Origin, const FVector2D& Destiny) const
{
    TArray<FVector2D> neighbours = GetPointNeighbours(Origin);
    int32 maxDistance = 1000000;
    int32 closestIdx = -1;
    for (int32 i = 0; i < neighbours.Num(); ++i)
    {
        int32 distance = (Destiny - neighbours[i]).SizeSquared();
        if (distance < maxDistance)
        {
            closestIdx = i;
            maxDistance = distance;
        }
    }
    if (closestIdx >= 0)
    {
        return neighbours[closestIdx];
    }
    return FVector2D();
}
