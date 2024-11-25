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
	
	/**
	*	UILLMVSimulationSubsystem::InitializeSimulation - public 
    *   @brief - When the world register a grid, the simulation can start running. Spawn entites and prepare targets for them
	*	@param AILLVMGrid * Grid
	*	@return void
	*/
	void InitializeSimulation(AILLVMGrid* Grid);

    /** Getter of the current grid representation*/
	const AILLVMGrid* GetCurrentGrid() const { return m_currentWorldGrid;}

    /**
    *	UILLMVSimulationSubsystem::RequestNewTarget - public 
    *   @brief - Look in which team is the given entity and find the closest other team entity as target
    *	@param AILLMVEntity * Entity
    *	@return AILLMVEntity*
    */
    AILLMVEntity* RequestNewTarget(AILLMVEntity* Entity) const;

private:
    
    /**
    *	UILLMVSimulationSubsystem::SpawnEntitiesForTeam - private 
    *   @brief - Internal method to spawn a team
    *	@param TSubclassOf<AILLMVEntity> Type
    *	@param int32 NumberOfEntities
    *	@param TArray<AILLMVEntity * > & TeamCollection
    *	@return void
    */
    void SpawnEntitiesForTeam(TSubclassOf<AILLMVEntity> Type, int32 NumberOfEntities, TArray<AILLMVEntity*>& TeamCollection);

    /**
    *	UILLMVSimulationSubsystem::SelectEntitiesTargets - private 
    *   @brief - Select targets to attack for both teams.
    *	@return void
    */
    void SelectEntitiesTargets();

    /**
    *	UILLMVSimulationSubsystem::SelectTargets - private 
    *   @brief - Iterate over attackers team to find closest targets in defender teams
    *	@param const TArray<AILLMVEntity * > & Attackers
    *	@param const TArray<AILLMVEntity * > & Defenders
    *	@return void
    */
    void SelectTargets(const TArray<AILLMVEntity*>& Attackers, const TArray<AILLMVEntity*>& Defenders);
    
    /**
    *	UILLMVSimulationSubsystem::SelectTargetForEntity - private 
    *   @brief - Given an entity, find the closest defender entity as target
    *	@param AILLMVEntity * Entity
    *	@param const TArray<AILLMVEntity * > & Defenders
    *	@return AILLMVEntity*
    */
    AILLMVEntity* SelectTargetForEntity(AILLMVEntity* Entity, const TArray<AILLMVEntity*>& Defenders) const;

    /**
    *	UILLMVSimulationSubsystem::StartSimulation - private 
    *   @brief - encapsulation method to select target for every time and start the simulation's timer
    *	@return void
    */
    void StartSimulation();

    /** Binding for the simulation timer. Every call update all entities simulation*/
    UFUNCTION()
    void SimulationStep();
private:

    //! Cached reference to the registered grid
	UPROPERTY(Transient)
	AILLVMGrid* m_currentWorldGrid = nullptr;

    //! Entities groped to team A
    UPROPERTY(Transient)
	TArray<AILLMVEntity*> m_teamA;

    //! Entities groped to team B
    UPROPERTY(Transient)
    TArray<AILLMVEntity*> m_teamB;

    //! Auxiliar entities collection to iterate easily over them
    UPROPERTY(Transient)
    TArray<AILLMVEntity*> m_allEntities;

    //! Cached refence to simulation timer
    UPROPERTY(Transient)
	FTimerHandle m_simulationStepTimer;
};
