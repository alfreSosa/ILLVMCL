// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulation/ILLMVSimulationSubsystem.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "ILLVMSimulationSettings.h"
#include "Engine/World.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::InitializeSimulation(AILLVMGrid* Grid)
{
    if (IsValid(Grid))
    {
        m_currentWorldGrid = Grid;
        SpawnEntitiesTeamA();
        //SpawnEntitiesTeamB();
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::SpawnEntitiesTeamA(int32 NumberOfEntities /*= 1*/)
{
    TSubclassOf<AILLMVEntity> entityClass = UILLVMSimulationSettings::Get().TeamAEntity;
    for (int32 i = 0; i < NumberOfEntities; ++i)
    {
        FVector2D gridLocation = m_currentWorldGrid->GetGridRandomLocation();
        AILLMVEntity* entity = GetWorld()->SpawnActor<AILLMVEntity>(entityClass);
        if (entity != nullptr)
        {
            entity->SetCurrentGridLocation(gridLocation);
            m_teamA.AddUnique(entity);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::SpawnEntitiesTeamB(int32 NumberOfEntities /*= 1*/)
{
    TSubclassOf<AILLMVEntity> entityClass = UILLVMSimulationSettings::Get().TeamBEntity;
    for (int32 i = 0; i < NumberOfEntities; ++i)
    {
        FVector2D gridLocation = m_currentWorldGrid->GetGridRandomLocation();
        AILLMVEntity* entity = GetWorld()->SpawnActor<AILLMVEntity>(entityClass);
        if (entity != nullptr)
        {
            entity->SetCurrentGridLocation(gridLocation);
            m_teamB.AddUnique(entity);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVSimulationSubsystem::StartSimulation()
{

}
