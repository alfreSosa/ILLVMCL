// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVIdleState.generated.h"

/**
 * Just a state where the entity should be doing nothing
 */
UCLASS()
class ILLVMCL_API UILLMVIdleState : public UILLMVState
{
	GENERATED_BODY()

public:
#pragma region UILLMVState
    /** Overridden to notify owner that should retunr to normal state*/
    virtual void EnterState() override;

    /** Overridden to transtitionate to moving state after owner has a target*/
    virtual void UpdateState() override;
#pragma endregion 
};
