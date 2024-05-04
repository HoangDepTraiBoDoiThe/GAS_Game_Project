// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UDamageGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	FORCEINLINE TMap<FGameplayTag, FScalableFloat> GetAbilityDamages() {return AbilityDamages;}
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> AbilityEffectClass;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FScalableFloat> AbilityDamages;
};
