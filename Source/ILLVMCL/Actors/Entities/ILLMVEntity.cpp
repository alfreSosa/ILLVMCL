// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

AILLMVEntity::AILLMVEntity(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

}

