// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ILLMVEntity.generated.h"

// Forward declarations
class UILLMVStateMachineComponent;

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
#pragma endregion
	
    const FVector2D& GetCurrentGridLocation() { return m_currentGridLocation; }
    void SetCurrentGridLocation(const FVector2D& GridLocation) { m_currentGridLocation = GridLocation; }

protected:
	//! Reference to state machine component which manage the entity state
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
	TObjectPtr<UILLMVStateMachineComponent> StateMachine = nullptr;

private:

	// Cached location of the entity in the grid
	FVector2D m_currentGridLocation = FVector2D::ZeroVector;


};
