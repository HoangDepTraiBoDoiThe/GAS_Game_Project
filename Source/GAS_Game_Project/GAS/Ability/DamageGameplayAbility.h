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
	FORCEINLINE TMap<FGameplayTag, FScalableFloat> GetAbilityDamageTypes() {return AbilityDamages;}
	TMap<FGameplayTag, float> GetAbilityDamagesAtLevel(const int32 Level = 1);
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	virtual FGameplayEffectSpecHandle MakeMyGameplayEffectSpecHandle() const;

	UFUNCTION(BlueprintCallable)
	void MakeSphereHitChecker(TArray<AActor*>& OverlapTargetActors, const UObject* WorldContextObject, const TArray<AActor*>& IgnoreActors, AActor* DamageCauser, const FVector& Origin, float DamageOuterRadius);
	
	UFUNCTION(BlueprintCallable)
	virtual void AppliedMyGameplayEffectToTarget(UAbilitySystemComponent* TargetASC);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> AbilityEffectClass;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FScalableFloat> AbilityDamages;
};
