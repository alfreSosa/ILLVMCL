// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVDeadState.generated.h"

/**
 * Representation of dead state of an entity
 * Force to no transition to another state
 */
UCLASS()
class ILLVMCL_API UILLMVDeadState : public UILLMVState
{
	GENERATED_BODY()

public:
#pragma region UILLMVState
    
    /** Overridden to notify owner actor the dead state*/
    virtual void EnterState() override; 

    /** Overridden to force not change state*/
    virtual bool CanChangeToState() override { return false;};

#pragma endregion
};
