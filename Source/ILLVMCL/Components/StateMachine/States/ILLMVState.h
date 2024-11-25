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
    *	UILLMVState::UpdateState - virtual public 
    *   @brief - Here subsclasses must implement custom logic.
    *	@return void
    */
    virtual void UpdateState() { }

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
