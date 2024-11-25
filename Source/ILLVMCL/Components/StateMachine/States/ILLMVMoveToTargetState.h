// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateMachine/States/ILLMVState.h"
#include "ILLMVMoveToTargetState.generated.h"

// Forward declarations
class AAILLMVEntity;

/**
 *  State of an entity in which is following a path or pursuing a target
 */
UCLASS()
class ILLVMCL_API UILLMVMoveToTargetState : public UILLMVState
{
	GENERATED_BODY()
	
public:
	/** Movement speed along the grid*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0), Category = "ILLVM|State|MoveToTarget")
	int32 TilesPerStepSpeed = 0;

	/** Grid unit to consider that the entity has reached an expected target*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0), Category = "ILLVM|State|MoveToTarget")
	int32 ReachTargetTilesDistance = 0;

public:
#pragma region UILLMVState
	
	/** Overridden to move along the path*/
	virtual void UpdateState() override;
#pragma endregion
	
	/** Method to receive a target to pursuit*/
	void SetCurrentTarget(AILLMVEntity* Target);
private:

	/** Internal method to check conditions about pursuit the target*/
	bool HasReachedTarget() const;

private:
	
	//! Current path location
	int32 m_pathIdx = 0;

	//! Received path to follow
	TArray<FVector2D> m_currentPath;

	//! Reference to possible target to pursuit
	UPROPERTY(Transient)
	AILLMVEntity* m_currentTarget = nullptr;
};
