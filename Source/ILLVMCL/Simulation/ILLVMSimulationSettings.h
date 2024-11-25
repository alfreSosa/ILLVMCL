// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Templates/SubclassOf.h"
#include "Actors/Entities/ILLMVEntity.h"
#include "ILLVMSimulationSettings.generated.h"

/**
 * Developer settings to define params of the simulation
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "ILLVM Simulation Settings")
class ILLVMCL_API UILLVMSimulationSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	//! Reference to team A class of the actors to spawn
	UPROPERTY(Config, EditDefaultsOnly, Category = "ILLVM")
	TSubclassOf<AILLMVEntity> TeamAEntity = nullptr;

	//! Number of team A entities to spawn
    UPROPERTY(Config, EditDefaultsOnly, meta = (ClampMin = 1), Category = "ILLVM")
	int32 TeamANumber = 1;

    //! Reference to team B class of the actors to spawn
    UPROPERTY(Config, EditDefaultsOnly, Category = "ILLVM")
    TSubclassOf<AILLMVEntity> TeamBEntity = nullptr;
    
    //! Number of team B entities to spawn
    UPROPERTY(Config, EditDefaultsOnly, meta = (ClampMin = 1), Category = "ILLVM")
    int32 TeamBNumber = 1;

	//! Time step simulation
    UPROPERTY(Config, EditDefaultsOnly, meta = (ClampMin = 0.1f), Category = "ILLVM")
	float SimulationTimeStep = 0.1f;

public:
	/**
	* @brief Convenience to easily access the configuration.
	*/
	static const UILLVMSimulationSettings& Get();
};
