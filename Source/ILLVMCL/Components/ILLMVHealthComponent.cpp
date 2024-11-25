// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ILLMVHealthComponent.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVHealthComponent::ApplyDamage(int32 DamageAmount)
{
	m_currentHealth = FMath::Max(m_currentHealth - DamageAmount, 0);
	m_ownerRef->GetStateMachine()->SetCurrentState(EILLMVEntityState::EReceiveHit);
	if (m_currentHealth <= 0)
	{
        OnDeadDelegate.Broadcast();
	}
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	m_ownerRef = Cast<AILLMVEntity>(GetOwner());
	m_currentHealth = FMath::RandRange(MinHealth, MaxHealth);
}

