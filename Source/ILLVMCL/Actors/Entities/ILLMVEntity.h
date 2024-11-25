// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ILLMVEntity.generated.h"

// Forward declarations
class UILLMVStateMachineComponent;
class UILLMVHealthComponent;
class URealTimeMovementComponent;

/** 
*	Base class for entities that will be placed in the simulation
*/
UCLASS()
class ILLVMCL_API AILLMVEntity : public AActor
{
	GENERATED_BODY()

public:
    /** Default constructor*/
    AILLMVEntity(const FObjectInitializer& ObjectInitializer);

#pragma region AILLMVEntity
    
	/**
	*	AILLMVEntity::UpdateSimulation - public 
    *   @brief - Should be called from simulation subsystem to update entity state
	*	@return void
	*/
	void UpdateSimulation();

    /** Getter for the state machine component*/
    TObjectPtr<UILLMVStateMachineComponent> GetStateMachine() { return StateMachine; }

    /** Getter for the health component*/
    TObjectPtr<UILLMVHealthComponent> GetHealthComponent() { return Health; }

    /** Getter for the real time movement component*/
    TObjectPtr<URealTimeMovementComponent> GetMovementComponent() { return Movement; }

    /** Getter of the current grid location assigned by the simulation*/
    const FVector2D& GetCurrentGridLocation() { return m_currentGridLocation; }
    
	/**
	*	AILLMVEntity::SetCurrentGridLocation - public 
    *   @brief - Receives a grid location and recover the world location to pass it to the real time movement component
	*	@param const FVector2D & GridLocation - Representation of the location in the grid coordinates
	*	@param bool Teleport - Flag to move the actor in the world location inmediatly
	*	@return void
	*/
	void SetCurrentGridLocation(const FVector2D& GridLocation, bool Teleport = false);

    /**
    *	AILLMVEntity::SetTarget - public 
    *   @brief - Assign a target to the entity
    *	@param AILLMVEntity * Target
    *	@return void
    */
    void SetTarget(AILLMVEntity* Target);

    /** Getter of the current target*/
	AILLMVEntity* GetTarget() const { return m_target; }

    /** Event blueprint to update the entity state feedback when entity is not doing anything special*/
    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnNormalState();

    /** Event blueprint to update the entity state feedback when entity is attacking*/
    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnAttackState();

    /** Event blueprint to update the entity state feedback when entity receives damage*/
    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnReceiveHit();

    /** Event blueprint to update the entity state feedback when entity loose all health points*/
    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnDeadState();

#pragma endregion
protected:
    /** Binding to the current target health component to receive when it is dead*/
    UFUNCTION()
    void OnTargetEntityDead();

protected:
	//! Reference to state machine component which manage the entity state
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
	TObjectPtr<UILLMVStateMachineComponent> StateMachine = nullptr;

    //! Reference to health component which manage the hits points and the transition to hit state
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
    TObjectPtr<UILLMVHealthComponent> Health = nullptr;

    //! Reference to real time movement component which interpolate the actor between world locations
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
    TObjectPtr<URealTimeMovementComponent> Movement = nullptr;

private:
    
    //! Cachced reference to the expected target
    UPROPERTY(Transient)
	AILLMVEntity* m_target = nullptr;
	
	// Cached location of the entity in the grid
	FVector2D m_currentGridLocation = FVector2D::ZeroVector;


};
