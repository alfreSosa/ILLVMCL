// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVMoveToTargetState.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "Simulation/ILLMVSimulationSubsystem.h"
#include "Engine/World.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVMoveToTargetState::EnterState()
{
    m_simulationSubsystem = GetWorld()->GetSubsystem<UILLMVSimulationSubsystem>();
    GetOwner()->OnNormalState();
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVMoveToTargetState::UpdateState()
{
    if (!HasReachedTarget())
    {
        FVector2D currentLocation = GetOwner()->GetCurrentGridLocation();
        FVector2D destiny = GetOwner()->GetTarget()->GetCurrentGridLocation(); // if has reached hasn't target, this code will not be executed
        for (int32 i = 0; i < TilesPerStepSpeed; ++i)
        {
            currentLocation = m_simulationSubsystem->GetCurrentGrid()->GetClosestNeighbourToPoint(currentLocation, destiny);
        }

        GetOwner()->SetCurrentGridLocation(currentLocation);
    }
    else
    {
        // pass to attack
        GetOwner()->GetStateMachine()->SetCurrentState(EILLMVEntityState::EAttack);
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

bool UILLMVMoveToTargetState::HasReachedTarget() const
{
    if (AILLMVEntity* target = GetOwner()->GetTarget())
    {
        FVector2D ownerGridLocation = GetOwner()->GetCurrentGridLocation();
        FVector2D targetGridLocation = target->GetCurrentGridLocation();

        int32 distanceToTarget = (targetGridLocation - ownerGridLocation).Size();
        return distanceToTarget <= ReachTargetTilesDistance;
    }
    return true; // Avoid movement if not target
}
