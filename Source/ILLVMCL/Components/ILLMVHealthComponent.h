// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ILLMVHealthComponent.generated.h"

class AILLMVEntity;

/**
* Component defined to manage the entities' hit points
* Generate automatically in begin play a random healh in the defined range
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ILLVMCL_API UILLMVHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//! Delegate signature to notify when the owner entity health has reached 0
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);

	//! Min hit points that the owner entity can suffer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 2, UIMin = 2, ClampMax = 6, UIMax = 6), Category = "ILLMV|Health")
	int32 MinHealth = 2;

    //! Max hit points that the owner entity can suffer
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 2, UIMin = 2, ClampMax = 6, UIMax = 6), Category = "ILLMV|Health")
    int32 MaxHealth = 6;

	//! Death delegate declaration. Broadcast happens when m_currentHealth is zero
    UPROPERTY(BlueprintAssignable)
	FOnDeadSignature OnDeadDelegate;

public:

	/** Getter of the curren health*/
	FORCEINLINE int32 GetCurrentHealth() const { return m_currentHealth; }

	/**
	*	UILLMVHealthComponent::ApplyDamage - public 
	*	@brief - Substract the damage amount to the health. Try to change entity to hit state and notify dead if procced.
	*	@param int32 DamageAmount
	*	@return void
	*/
	void ApplyDamage(int32 DamageAmount);

protected:
#pragma region UActorComponent
	/** Overridden to initialize health to a random value*/
	virtual void BeginPlay() override;
#pragma endregion
private:
	//! Cached value of current health. Initialize in begin play through random
	int32 m_currentHealth = 0;

	//! Cached reference to owner
	UPROPERTY(Transient)
	AILLMVEntity* m_ownerRef = nullptr;
};
