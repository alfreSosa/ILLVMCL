// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RealTimeMovementComponent.generated.h"

class AILLMVEntity;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ILLVMCL_API URealTimeMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ILLMV|RealTimeMovement")
	float Speed = 2.0f;

public:	

	/** Default constructor*/
	URealTimeMovementComponent(const FObjectInitializer& ObjectInitializer);
	
	/** Overridden to interpolate owners location while moving*/
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetTargetLocation(const FVector& TargetWorldLocation);

protected:
	virtual void BeginPlay() override;
	bool HasReachedTargetLocation() const;

private:

	UPROPERTY(Transient)
	AILLMVEntity* m_ownerRef = nullptr;

	FVector m_targetLocation = FVector::ZeroVector;
		
};
