// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVIdleState.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVIdleState::UpdateState()
{
    if (GetOwner()->HasDestiny())
    {
        GetOwner()->GetStateMachine()->SetCurrentState(EILLMVEntityState::EMovingToTarget);
    }
}
