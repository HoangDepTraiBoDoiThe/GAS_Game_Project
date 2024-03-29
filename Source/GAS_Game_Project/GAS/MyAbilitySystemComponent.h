// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAttributevalueChangeBroadcastToControllerSignature, const FOnAttributeChangeData&)
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEffectTagsBroadcastToControllerSignature, const FGameplayTagContainer&)


UCLASS()
class GAS_GAME_PROJECT_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputTagHeld(FGameplayTag& InputTag);
	void AbilityInputTagReleased(FGameplayTag& InputTag);
	void InitOwnerAndAvatarActor(AActor* OwnerActor, AActor* AvatarActor);
	void BindCallBackToDependencies();
	void AddAbilities(TArray<TSubclassOf<UGameplayAbility>>, float);

	FGameplayAttributevalueChangeBroadcastToControllerSignature OnNewAttributeValueChangeBroadcastToControllerDelegate;
	FGameplayEffectTagsBroadcastToControllerSignature GameplayEffectTagsBroadcastToControllerDelegate;

};
