// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVHitState.generated.h"

/**
 * 
 */
UCLASS()
class ILLVMCL_API UILLMVHitState : public UILLMVState
{
	GENERATED_BODY()

public:
#pragma region UILLMVState

    virtual void EnterState() override;

    /** Overridden to move along the path*/
    virtual void UpdateState() override;
#pragma endregion

private:
    EILLMVEntityState m_previousState = EILLMVEntityState::EIdle;
};
