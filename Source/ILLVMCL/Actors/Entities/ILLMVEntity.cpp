// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Entities/ILLMVEntity.h"
#include "Components/StateMachine/ILLMVStateMachineComponent.h"
#include "Engine/World.h"
#include "Actors/Grid/ILLVMGrid.h"
#include "Simulation/ILLMVSimulationSubsystem.h"
#include "Components/ILLMVHealthComponent.h"
#include "Components/RealTimeMovementComponent.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

AILLMVEntity::AILLMVEntity(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

    StateMachine = CreateDefaultSubobject<UILLMVStateMachineComponent>(TEXT("StateMachine"));
    Health = CreateDefaultSubobject<UILLMVHealthComponent>(TEXT("Health"));
    Movement = CreateDefaultSubobject<URealTimeMovementComponent>(TEXT("Movement"));

}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVEntity::UpdateSimulation()
{
    StateMachine->UpdateState();
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVEntity::SetCurrentGridLocation(const FVector2D& GridLocation, bool Teleport /*= false*/)
{
    m_currentGridLocation = GridLocation;
    UILLMVSimulationSubsystem* simulationSubsystem = GetWorld()->GetSubsystem<UILLMVSimulationSubsystem>();
    if (simulationSubsystem != nullptr)
    {
        const AILLVMGrid* grid = simulationSubsystem->GetCurrentGrid();
        if (grid != nullptr)
        {
            FVector worldLocation = grid->GetGridWorldLocation(m_currentGridLocation);
            if (Teleport)
            {
                SetActorLocation(worldLocation);
            }
            Movement->SetTargetLocation(worldLocation);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVEntity::SetTarget(AILLMVEntity* Target)
{
    if (m_target != nullptr && m_target != Target)
    {
        m_target->GetHealthComponent()->OnDeadDelegate.RemoveDynamic(this, &AILLMVEntity::OnTargetEntityDead);
    }
    m_target = Target;
    m_target->GetHealthComponent()->OnDeadDelegate.AddDynamic(this, &AILLMVEntity::OnTargetEntityDead);
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void AILLMVEntity::OnTargetEntityDead()
{
    if (m_target != nullptr)
    {
        m_target->GetHealthComponent()->OnDeadDelegate.RemoveDynamic(this, &AILLMVEntity::OnTargetEntityDead);
    }
    m_target = nullptr;

    // Return to idle after losing the target
    GetStateMachine()->SetCurrentState(EILLMVEntityState::EIdle);
}

