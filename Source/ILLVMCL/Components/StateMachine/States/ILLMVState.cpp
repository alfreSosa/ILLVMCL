// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVState.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void UILLMVState::Initialize(AILLMVEntity* Owner)
{
    m_owner = Owner;
}
