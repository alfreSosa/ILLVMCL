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

	TObjectPtr<UILLMVStateMachineComponent> GetStateMachine() { return StateMachine;}

    const FVector2D& GetCurrentGridLocation() { return m_currentGridLocation; }
    
	void SetCurrentGridLocation(const FVector2D& GridLocation);

    void SetMovementDestiny(const FVector2D& Destiny);

    bool HasDestiny() const { return m_destiny.IsSet(); }

    FVector2D GetDestiny() const { return *m_destiny; }

#pragma endregion
protected:
	//! Reference to state machine component which manage the entity state
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|Enitity")
	TObjectPtr<UILLMVStateMachineComponent> StateMachine = nullptr;

private:

    TOptional<FVector2D> m_destiny;
	
	// Cached location of the entity in the grid
	FVector2D m_currentGridLocation = FVector2D::ZeroVector;


};
