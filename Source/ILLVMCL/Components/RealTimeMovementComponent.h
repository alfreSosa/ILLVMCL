// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RealTimeMovementComponent.generated.h"

class AILLMVEntity;

/**
* Component to move the actor in world location smoothly.
* Tries to move between current actor location and the expected world grid location
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ILLVMCL_API URealTimeMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//! How fast the entity move in world position
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|RealTimeMovement")
	float Speed = 2.0f;

public:	

	/** Default constructor*/
	URealTimeMovementComponent(const FObjectInitializer& ObjectInitializer);
	
	/** Overridden to interpolate owners location while moving*/
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/**
	*	URealTimeMovementComponent::SetTargetLocation - public 
	*	@brief - Update the expected target location to reach. Also ensures that the entity has not already reach the target to start ticking.
	*	@param const FVector & TargetWorldLocation
	*	@return void
	*/
	void SetTargetLocation(const FVector& TargetWorldLocation);

protected:
	/** Overridden to recover reference to the owner*/
	virtual void BeginPlay() override;

	/** Internal method that check the distance between the owner's location and the expected target*/
	bool HasReachedTargetLocation() const;

private:
	//! Cached reference to owner
	UPROPERTY(Transient)
	AILLMVEntity* m_ownerRef = nullptr;

	//! Cached world location where the owner should move smoothly
	FVector m_targetLocation = FVector::ZeroVector;
		
};
