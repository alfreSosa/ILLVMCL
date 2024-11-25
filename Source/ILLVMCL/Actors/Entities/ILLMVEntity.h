// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ILLMVEntity.generated.h"

// Forward declarations
class UILLMVStateMachineComponent;
class UILLMVHealthComponent;

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

	void UpdateSimulation();

    TObjectPtr<UILLMVStateMachineComponent> GetStateMachine() { return StateMachine; }
    TObjectPtr<UILLMVHealthComponent> GetHealthComponent() { return Health; }

    const FVector2D& GetCurrentGridLocation() { return m_currentGridLocation; }
    
	void SetCurrentGridLocation(const FVector2D& GridLocation);

    void SetTarget(AILLMVEntity* Target);

	AILLMVEntity* GetTarget() const { return m_target; }

    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnNormalState();

    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnAttackState();

    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnReceiveHit();

    UFUNCTION(BlueprintImplementableEvent, Category = "ILLMV|Enitity")
    void OnDeadState();

#pragma endregion
protected:
    UFUNCTION()
    void OnTargetEntityDead();

protected:
	//! Reference to state machine component which manage the entity state
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
	TObjectPtr<UILLMVStateMachineComponent> StateMachine = nullptr;

    //! Reference to state machine component which manage the entity state
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
    TObjectPtr<UILLMVHealthComponent> Health = nullptr;

private:

    UPROPERTY(Transient)
	AILLMVEntity* m_target = nullptr;
	
	// Cached location of the entity in the grid
	FVector2D m_currentGridLocation = FVector2D::ZeroVector;


};
