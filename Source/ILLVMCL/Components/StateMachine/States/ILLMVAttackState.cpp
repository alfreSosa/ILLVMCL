// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVAttackState.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "Components/ILLMVHealthComponent.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVAttackState::EnterState()
{
    m_currenRateTimer = 0;
    GetOwner()->OnNormalState();
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVAttackState::UpdateState()
{
    if (AILLMVEntity* target = GetOwner()->GetTarget())
    {
        ++m_currenRateTimer;
        GetOwner()->OnNormalState();
        if (m_currenRateTimer >= AttackRate)
        {
            GetOwner()->OnAttackState();
            target->GetHealthComponent()->ApplyDamage(AttackDamage);
            m_currenRateTimer = 0;
        }
    }
}
