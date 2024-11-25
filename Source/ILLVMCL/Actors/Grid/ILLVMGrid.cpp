// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Grid/ILLVMGrid.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

AILLVMGrid::AILLVMGrid(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	// Not need of ticking
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLVMGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GenerateGrid();
}

