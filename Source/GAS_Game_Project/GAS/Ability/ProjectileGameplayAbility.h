// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "ProjectileGameplayAbility.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UProjectileGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	FORCEINLINE FScalableFloat GetAbilityDamage() {return AbilityDamage;}
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FVector TargetLocation);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseProjectile> AbilityProjectileClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> AbililyEffectClass;

	UPROPERTY(EditAnywhere)
	FScalableFloat AbilityDamage;
};
