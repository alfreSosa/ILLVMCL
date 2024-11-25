// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ILLMVState.generated.h"

// Forward declarations
class AILLMVEntity;

/**
 * Base class to define the interface of the entities' states
 */
UCLASS(EditInlineNew , Abstract)
class ILLVMCL_API UILLMVState : public UObject
{
	GENERATED_BODY()

public:
    
    /**
    *	UILLMVState::Initialize - virtual public 
    *   @brief - class initialization method to get a reference to owner entity. Subclasses can implement custom initialization here. Dont forget to call super
    *	@param AILLMVEntity * Owner
    *	@return void
    */
    virtual void Initialize(AILLMVEntity* Owner);

    /**
    *	UILLMVState::EnterState - virtual public 
    *   @brief - This method is called everytime a state is activated
    *	@return void
    */
    virtual void EnterState() { }

    /**
    *	UILLMVState::EnterState - virtual public
    *   @brief - This method is called everytime exit from the state
    *	@return void
    */
    virtual void ExistState() { }
    /**
    *	UILLMVState::UpdateState - virtual public 
    *   @brief - Called every simulation step. Here subclasses must implement custom logic.
    *	@return void
    */
    virtual void UpdateState() { }

    /**
    *	UILLMVState::CanChangeToState - virtual public
        @brief - This method is called everytime a state change is requested to the state machine.
    *	@return bool
    */
    virtual bool CanChangeToState() { return true; }
    
    /**
    *	UILLMVState::GetOwner - public 
    *   @brief - Getter of the entity owner
    *	@return FORCEINLINE AILLMVEntity*
    */
    FORCEINLINE AILLMVEntity* GetOwner() const { return m_owner; }

private: 
    //! Cached referenced to owner
    UPROPERTY(Transient)
    AILLMVEntity* m_owner = nullptr;
};
