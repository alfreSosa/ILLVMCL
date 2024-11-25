// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Entities/ILLMVEntity.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "Engine/World.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "Simulation/ILLMVSimulationSubsystem.h"

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

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVEntity::SetCurrentGridLocation(const FVector2D& GridLocation)
{
    m_currentGridLocation = GridLocation;
    UILLMVSimulationSubsystem* simulationSubsystem = GetWorld()->GetSubsystem<UILLMVSimulationSubsystem>();
    if (simulationSubsystem != nullptr)
    {
        const AILLVMGrid* grid = simulationSubsystem->GetCurrentGrid();
        if (grid != nullptr)
        {
            SetActorLocation(grid->GetGridWorldLocation(m_currentGridLocation));
        }
    }
}

