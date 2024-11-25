// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ILLMVSimulationSubsystem.generated.h"

class AILLVMGrid;
class AILLMVEntity;

/**
 * Subsystem to manage the simulation and execute simulation per time step
 */
UCLASS()
class ILLVMCL_API UILLMVSimulationSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	void InitializeSimulation(AILLVMGrid* Grid);

	const AILLVMGrid* GetCurrentGrid() const { return m_currentWorldGrid;}

    AILLMVEntity* RequestNewTarget(AILLMVEntity* Entity) const;

private:

    void SpawnEntitiesForTeam(TSubclassOf<AILLMVEntity> Type, int32 NumberOfEntities, TArray<AILLMVEntity*>& TeamCollection);

    void SelectEntitiesTargets();

    void SelectTargets(const TArray<AILLMVEntity*>& Attackers, const TArray<AILLMVEntity*>& Defenders);
    
    AILLMVEntity* SelectTargetForEntity(AILLMVEntity* Entity, const TArray<AILLMVEntity*>& Defenders) const;

    void StartSimulation();

    UFUNCTION()
    void SimulationStep();
private:

	UPROPERTY(Transient)
	AILLVMGrid* m_currentWorldGrid = nullptr;

    UPROPERTY(Transient)
	TArray<AILLMVEntity*> m_teamA;

    UPROPERTY(Transient)
    TArray<AILLMVEntity*> m_teamB;

    UPROPERTY(Transient)
    TArray<AILLMVEntity*> m_allEntities;

    UPROPERTY(Transient)
	FTimerHandle m_simulationStepTimer;
};
