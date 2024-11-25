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
	bool canChangeState = true;
	if (IsValid(m_currentState))
	{
		// Ensure current state allows to change state
		canChangeState = m_currentState->CanChangeToState();
	}

	if (canChangeState)
	{
		TObjectPtr<UILLMVState>* targetState = States.Find(State);
		if (targetState != nullptr)
		{
			// if already in a state, then exit from it
            if (IsValid(m_currentState))
            {
				m_currentState->ExistState();
			}
			// Cache current state
			m_currentStateType = State;
			m_currentState = *targetState;
			// notify state that has entered
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

