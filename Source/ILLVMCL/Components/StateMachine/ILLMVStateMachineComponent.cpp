// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "States/ILLMVState.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

UILLMVStateMachineComponent::UILLMVStateMachineComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVStateMachineComponent::SetCurrentState(EILLMVEntityState State)
{
	// Assuming that state can change always and only depends on the current state
	bool canChangeState = true;
	if (IsValid(m_currentState))
	{
		canChangeState = m_currentState->CanChangeToState();
	}

	if (canChangeState)
	{
		TObjectPtr<UILLMVState>* targetState = States.Find(State);
		if (targetState != nullptr)
		{
            if (IsValid(m_currentState))
            {
				m_currentState->ExistState();
			}
			m_currentState = *targetState;
			m_currentState->EnterState();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVStateMachineComponent::UpdateState()
{
    if (IsValid(m_currentState))
    {
		m_currentState->UpdateState();
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

UILLMVState* UILLMVStateMachineComponent::GetState(EILLMVEntityState State)
{
    TObjectPtr<UILLMVState>* targetState = States.Find(State);
    if (targetState != nullptr)
    {
        return *targetState;
    }
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	// Initialize all states
	for (auto pairState : States)
	{
		pairState.Value->Initialize(Cast<AILLMVEntity>(GetOwner()));
	}

	// Define a default first state for the entity owner
	SetCurrentState(EILLMVEntityState::EIdle);
}

