// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVHitState.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "Components/ILLMVHealthComponent.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVHitState::EnterState()
{
    GetOwner()->OnReceiveHit();
    m_previousState = GetOwner()->GetStateMachine()->GetCurrentState();
    // if not life, next simulation step should be dead
    if (GetOwner()->GetHealthComponent()->GetCurrentHealth() <= 0)
    {
        m_previousState = EILLMVEntityState::EDead;
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVHitState::UpdateState()
{
    // Just one simulation step to return to previous state
    GetOwner()->GetStateMachine()->SetCurrentState(m_previousState);
}
