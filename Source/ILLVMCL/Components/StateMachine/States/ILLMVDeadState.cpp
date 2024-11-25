// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateMachine/States/ILLMVDeadState.h"
#include "Actors/Entities/ILLMVEntity.h"

void UILLMVDeadState::EnterState()
{
    GetOwner()->OnDeadState();
}