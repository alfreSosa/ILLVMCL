// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVMoveToTargetState.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVMoveToTargetState::UpdateState()
{
    if (!HasReachedTarget())
    {
        m_pathIdx += TilesPerStepSpeed;
        // Ensure no break the path
        if (m_pathIdx >= m_currentPath.Num())
        {
            m_pathIdx = m_currentPath.Num() - 1;
        }
        if (m_pathIdx >= 0)
        {
            GetOwner()->SetCurrentGridLocation(m_currentPath[m_pathIdx]);
        }
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
