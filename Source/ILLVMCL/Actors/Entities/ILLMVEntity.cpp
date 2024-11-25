// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Entities/ILLMVEntity.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

AILLMVEntity::AILLMVEntity(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

    StateMachine = CreateDefaultSubobject<UILLMVStateMachineComponent>(TEXT("StateMachine"));

}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVEntity::UpdateSimulation()
{
    StateMachine->UpdateState();
}

