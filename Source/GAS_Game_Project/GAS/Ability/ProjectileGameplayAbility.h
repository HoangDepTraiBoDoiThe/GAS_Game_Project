// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "ProjectileGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UProjectileGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
