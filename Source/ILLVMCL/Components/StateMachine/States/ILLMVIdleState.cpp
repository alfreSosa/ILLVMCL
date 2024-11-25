// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVIdleState.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVIdleState::EnterState()
{
    // Notify return to normal state
    GetOwner()->OnNormalState();
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVIdleState::UpdateState()
{
    if (GetOwner()->GetTarget() != nullptr)
    {
        GetOwner()->GetStateMachine()->SetCurrentState(EILLMVEntityState::EMovingToTarget);
    }
}
