// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ILLMVStateMachineComponent.generated.h"

// Forward declarations
class UILLMVState;

/**
* Enum definition for possibles state of the entities during the simulation
*/
UENUM(BlueprintType)
enum class EILLMVEntityState : uint8
{
	EIdle = 0,
	EMovingToTarget,
	EAttack,
	EReceiveHit,
	EDead,
};

/**
* Very simple implementation of state machine.
* Manage the several states that the entity of the simulation can be.
* Mainly update the current state of the entity and also update the transitions between states when is needed. 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ILLVMCL_API UILLMVStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/** Defined states for owner entity*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ILLVM|StateMachine")
	TMap<EILLMVEntityState, TObjectPtr<UILLMVState>> States;

public:	
	/** Default constructor*/
	UILLMVStateMachineComponent(const FObjectInitializer& ObjectInitializer);

#pragma region UILLMVStateMachineComponent
	
	/**
	*	UILLMVStateMachineComponent::SetCurrentState - public 
	*	@brief - method that try to changes the current state of the entity
	*	@param EILLMVEntityState State
	*	@return void
	*/
	void SetCurrentState(EILLMVEntityState State);

	/**
	*	UILLMVStateMachineComponent::UpdateState - public 
	*	@brief - Update the active state and check possible transition between states
	*	@return void
	*/
	void UpdateState();
	
	/**
	*	UILLMVStateMachineComponent::GetState - public 
	*	@brief - Getter of the instance of a state
	*	@param EILLMVEntityState State
	*	@return UILLMVState*
	*/
	UILLMVState* GetState(EILLMVEntityState State);

	FORCEINLINE EILLMVEntityState GetCurrentState() const { return m_currentStateType;}

#pragma endregion

protected:
#pragma region UActorComponent
	/** Overridden to initialize state and set a default first state*/
	virtual void BeginPlay() override;
#pragma endregion

private:
	UPROPERTY(Transient)
	EILLMVEntityState m_currentStateType = EILLMVEntityState::EMovingToTarget;
	//! Chached reference of the active state
	UPROPERTY(Transient)
	UILLMVState* m_currentState = nullptr;
};
