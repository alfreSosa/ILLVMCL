// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVHitState.generated.h"

/**
 * State of entity when receive damage.
 * Next simulation step will return to the previous state
 * If entity is already without health, transition to dead state
 */
UCLASS()
class ILLVMCL_API UILLMVHitState : public UILLMVState
{
	GENERATED_BODY()

public:
#pragma region UILLMVState

    /** Overridden to notify the owner that has received a hit*/
    virtual void EnterState() override;

    /** Overridden to return to the previous state after one simulation step*/
    virtual void UpdateState() override;
#pragma endregion

private:
    EILLMVEntityState m_previousState = EILLMVEntityState::EIdle;
};
