// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulation/ILLMVSimulationSubsystem.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "ILLVMSimulationSettings.h"
#include "Engine/World.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "TimerManager.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::InitializeSimulation(AILLVMGrid* Grid)
{
    if (IsValid(Grid))
    {
        m_currentWorldGrid = Grid;
        SpawnEntitiesForTeam(UILLVMSimulationSettings::Get().TeamAEntity, UILLVMSimulationSettings::Get().TeamANumber, m_teamA);
        SpawnEntitiesForTeam(UILLVMSimulationSettings::Get().TeamBEntity, UILLVMSimulationSettings::Get().TeamBNumber, m_teamB);
        StartSimulation();
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::SpawnEntitiesForTeam(TSubclassOf<AILLMVEntity> Type, int32 NumberOfEntities, TArray<AILLMVEntity*>& TeamCollection)
{
    for (int32 i = 0; i < NumberOfEntities; ++i)
    {
        FVector2D gridLocation = m_currentWorldGrid->GetGridRandomLocation();
        AILLMVEntity* entity = GetWorld()->SpawnActor<AILLMVEntity>(Type);
        if (entity != nullptr)
        {
            entity->SetCurrentGridLocation(gridLocation);
            TeamCollection.AddUnique(entity);
            m_allEntities.AddUnique(entity);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::SelectEntitiesTargets()
{
    SelectTargets(m_teamA, m_teamB);
    SelectTargets(m_teamB, m_teamA);
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::SelectTargets(const TArray<AILLMVEntity*>& Attackers, const TArray<AILLMVEntity*>& Defenders)
{
    for (int32 i = 0; i < Attackers.Num(); ++i)
    {
        FVector2D location = Attackers[i]->GetCurrentGridLocation();
        AILLMVEntity* targetEntity = nullptr;
        int32 maxDistance = MAX_int32;
        for (int32 j = 0; j < Defenders.Num(); ++j)
        {
            int32 distance = (Defenders[j]->GetCurrentGridLocation() - location).SizeSquared();
            if (distance < maxDistance)
            {
                maxDistance = distance;
                targetEntity = Defenders[j];
            }
        }
        Attackers[i]->SetTarget(targetEntity);
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::StartSimulation()
{
    // Temporal code to generate paths
    SelectEntitiesTargets();
    GetWorld()->GetTimerManager().SetTimer(m_simulationStepTimer, this, &UILLMVSimulationSubsystem::SimulationStep, UILLVMSimulationSettings::Get().SimulationTimeStep, true);
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::SimulationStep()
{
    for (AILLMVEntity* entity : m_allEntities)
    {
        entity->UpdateSimulation();
    }
}
