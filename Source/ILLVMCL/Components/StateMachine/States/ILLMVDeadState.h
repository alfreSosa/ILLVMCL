// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVDeadState.generated.h"

/**
 * 
 */
UCLASS()
class ILLVMCL_API UILLMVDeadState : public UILLMVState
{
	GENERATED_BODY()

public:
#pragma region UILLMVState

    virtual void EnterState() override;

#pragma endregion
};
