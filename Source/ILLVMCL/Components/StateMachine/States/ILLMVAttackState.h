// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVAttackState.generated.h"

/**
 * 
 */
UCLASS()
class ILLVMCL_API UILLMVAttackState : public UILLMVState
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1), Category = "ILLVM|State|Attack")
    int32 AttackRate = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1), Category = "ILLVM|State|Attack")
    int32 AttackDamage = 1;

public:
#pragma region UILLMVState

    virtual void EnterState() override;

    /** Overridden to move along the path*/
    virtual void UpdateState() override;
#pragma endregion

private:
    int32 m_currenRateTimer = 0;
};
