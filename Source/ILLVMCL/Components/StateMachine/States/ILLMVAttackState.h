// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVAttackState.generated.h"

/**
 * State of an entity when is in the minimun distance to attack it
 */
UCLASS()
class ILLVMCL_API UILLMVAttackState : public UILLMVState
{
	GENERATED_BODY()

public:
    
    //! Number of simulation's time steps to execute an attack
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1), Category = "ILLVM|State|Attack")
    int32 AttackRate = 1;

    //! Hit points to remove to the target when attack
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1), Category = "ILLVM|State|Attack")
    int32 AttackDamage = 1;

public:
#pragma region UILLMVState

    /** Overridden to reset the attack rate and set it to normal state*/
    virtual void EnterState() override;

    /** Overridden to attack every AttackRate time steps*/
    virtual void UpdateState() override;
#pragma endregion

private:
    //! Internal rate time steps passed since last attack
    int32 m_currenRateTimer = 0;
};
