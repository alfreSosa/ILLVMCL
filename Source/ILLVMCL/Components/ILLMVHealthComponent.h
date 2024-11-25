// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ILLMVHealthComponent.generated.h"

class AILLMVEntity;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ILLVMCL_API UILLMVHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 2, UIMin = 2, ClampMax = 6, UIMax = 6), Category = "ILLMV|Health")
	int32 MinHealth = 2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 2, UIMin = 2, ClampMax = 6, UIMax = 6), Category = "ILLMV|Health")
    int32 MaxHealth = 6;

    UPROPERTY(BlueprintAssignable)
	FOnDeadSignature OnDeadDelegate;

public:

	FORCEINLINE int32 GetCurrentHealth() const { return m_currentHealth; }

	void ApplyDamage(int32 DamageAmount);

protected:
#pragma region UActorComponent
	/** Overridden to initialize health to a random value*/
	virtual void BeginPlay() override;
#pragma endregion
private:

	int32 m_currentHealth = 0;

	UPROPERTY(Transient)
	AILLMVEntity* m_ownerRef = nullptr;
};
