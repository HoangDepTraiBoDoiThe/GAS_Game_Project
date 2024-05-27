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
DECLARE_DELEGATE_OneParam(FActivatableAbilitiesAddedSignature, const UAbilitySystemComponent*)


UCLASS()
class GAS_GAME_PROJECT_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputTagHeld(FGameplayTag& InputTag);
	void AbilityInputTagReleased(FGameplayTag& InputTag);
	void InitOwnerAndAvatarActor(AActor* OwnerActor, AActor* AvatarActor);
	void BindCallBackToDependencies();
	void AddAbilities(TArray<TSubclassOf<UGameplayAbility>>, float Level = 1);
	void AddEventReceiver(TSubclassOf<UGameplayAbility> EventReceiverAbilityClass, int32 Level);
	void BindGameplayAttrValChangeCallback(); // Should call BindCallBackToDependencies() instead
	void UnlockAbility(TSubclassOf<UGameplayAbility> AbilityToUnlock);

	FGameplayAttributevalueChangeBroadcastToControllerSignature OnNewAttributeValueChangeBroadcastToControllerDelegate;
	FGameplayEffectTagsBroadcastToControllerSignature GameplayEffectTagsBroadcastToControllerDelegate;
	FActivatableAbilitiesAddedSignature AbilitiesAddedDelegate;

	bool bAbilitiesAdded;
	
private:
	// When ASC gave Abilities to the player, it should also notify the UI to show it.
	UFUNCTION(Client, Reliable)
	void Client_ActivatableAbilitiesAdded();
	void BindGameplayEffectCallback();
};
