// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RealTimeMovementComponent.h"
#include "Actors/Entities/ILLMVEntity.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

URealTimeMovementComponent::URealTimeMovementComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{

    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void URealTimeMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector currentLocation = m_ownerRef->GetActorLocation();
	m_ownerRef->SetActorLocation(FMath::VInterpTo(currentLocation, m_targetLocation, DeltaTime, Speed));
    SetComponentTickEnabled(!HasReachedTargetLocation());
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void URealTimeMovementComponent::SetTargetLocation(const FVector& TargetWorldLocation)
{
	m_targetLocation = TargetWorldLocation;
	// distance to target, not squared to easy debug
	SetComponentTickEnabled(!HasReachedTargetLocation());
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

void URealTimeMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	m_ownerRef = Cast<AILLMVEntity>(GetOwner());
}

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

bool URealTimeMovementComponent::HasReachedTargetLocation() const
{
	float distance = (m_ownerRef->GetActorLocation() - m_targetLocation).Size();
	return FMath::IsNearlyZero(distance, 0.01);
}

