// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulation/ILLMVSimulationSubsystem.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "ILLVMSimulationSettings.h"
#include "Engine/World.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "TimerManager.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"

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

AILLMVEntity* UILLMVSimulationSubsystem::RequestNewTarget(AILLMVEntity* Entity) const
{
    if (m_teamA.Contains(Entity))
    {
        return SelectTargetForEntity(Entity, m_teamB);
    }
    // assume is team b
    return SelectTargetForEntity(Entity, m_teamA);
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
            entity->SetCurrentGridLocation(gridLocation, true);
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
        Attackers[i]->SetTarget(SelectTargetForEntity(Attackers[i], Defenders));
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

AILLMVEntity* UILLMVSimulationSubsystem::SelectTargetForEntity(AILLMVEntity* Entity, const TArray<AILLMVEntity*>& Defenders) const
{
    FVector2D location = Entity->GetCurrentGridLocation();
    AILLMVEntity* targetEntity = nullptr;
    int32 maxDistance = MAX_int32;
    for (int32 j = 0; j < Defenders.Num(); ++j)
    {
        if (Defenders[j]->GetStateMachine()->GetCurrentState() != EILLMVEntityState::EDead)
        {
            int32 distance = (Defenders[j]->GetCurrentGridLocation() - location).SizeSquared();
            if (distance < maxDistance)
            {
                maxDistance = distance;
                targetEntity = Defenders[j];
            }
        }
    }
    return targetEntity;
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
