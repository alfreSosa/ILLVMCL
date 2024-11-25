// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVMoveToTargetState.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "Simulation/ILLMVSimulationSubsystem.h"
#include "Engine/World.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVMoveToTargetState::EnterState()
{
    m_simulationSubsystem = GetWorld()->GetSubsystem<UILLMVSimulationSubsystem>();
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVMoveToTargetState::UpdateState()
{
    if (!HasReachedTarget())
    {
        FVector2D currentLocation = GetOwner()->GetCurrentGridLocation();
        FVector2D destiny = GetOwner()->GetDestiny();
        for (int32 i = 0; i < TilesPerStepSpeed; ++i)
        {
            currentLocation = m_simulationSubsystem->GetCurrentGrid()->GetClosestNeighbourToPoint(currentLocation, destiny);
        }

        GetOwner()->SetCurrentGridLocation(currentLocation);
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVMoveToTargetState::SetCurrentTarget(AILLMVEntity* Target)
{
    m_currentTarget = Target;
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

bool UILLMVMoveToTargetState::HasReachedTarget() const
{
    if (m_currentTarget == nullptr)
    {
        return false;
    }

    FVector2D ownerGridLocation = GetOwner()->GetCurrentGridLocation();
    FVector2D targetGridLocation = m_currentTarget->GetCurrentGridLocation();

    int32 distanceToTarget = (targetGridLocation - ownerGridLocation).Size();
    return distanceToTarget <= ReachTargetTilesDistance;
}
