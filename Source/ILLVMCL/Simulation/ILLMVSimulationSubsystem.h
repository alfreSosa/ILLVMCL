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

	void SpawnEntitiesTeamA(int32 NumberOfEntities = 1);

    void SpawnEntitiesTeamB(int32 NumberOfEntities = 1);

	void StartSimulation();

	const AILLVMGrid* GetCurrentGrid() const { return m_currentWorldGrid;}
private:

	UPROPERTY(Transient)
	AILLVMGrid* m_currentWorldGrid = nullptr;

    UPROPERTY(Transient)
	TArray<AILLMVEntity*> m_teamA;

    UPROPERTY(Transient)
    TArray<AILLMVEntity*> m_teamB;
};
