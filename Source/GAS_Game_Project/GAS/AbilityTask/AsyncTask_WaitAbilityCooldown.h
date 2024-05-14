// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTask_WaitAbilityCooldown.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaitCooldownSignature, float, CooldownTime);

class UAbilitySystemComponent;

UCLASS(BlueprintType, meta=(ExposedAsyncProxy="AsyncTask"))
class GAS_GAME_PROJECT_API UAsyncTask_WaitAbilityCooldown : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="TRUE"))
	static UAsyncTask_WaitAbilityCooldown* WaitAbilityCooldown(UAbilitySystemComponent* ASC, FGameplayTag CooldownTag);
	UFUNCTION(BlueprintCallable)
	void EndTask();

	UPROPERTY(BlueprintAssignable)
	FOnWaitCooldownSignature StartCooldownDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnWaitCooldownSignature EndCooldownDelegate;
private:
	void OnCooldownTagChange(const FGameplayTag, int32) const;
	void OnStartCooldown(UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle) const;
	
	TObjectPtr<UAbilitySystemComponent> OwningASC;
	FGameplayTag OwningCooldownTag;
	
};
