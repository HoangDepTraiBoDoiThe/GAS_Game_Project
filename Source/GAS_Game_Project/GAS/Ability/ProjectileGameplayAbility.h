// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "DamageGameplayAbility.h"
#include "ProjectileGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UProjectileGameplayAbility : public UDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FVector TargetLocation) const;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseProjectile> AbilityProjectileClass;
};
