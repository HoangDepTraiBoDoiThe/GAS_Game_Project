// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/UserInterface/Controller/BaseWidgetController.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */

class UBaseGameplayAbility;
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAttributevalueChangeBroadcastToControllerSignature,
                                    const FOnAttributeChangeData&)
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEffectTagsBroadcastToControllerSignature, const FGameplayTagContainer&)
DECLARE_MULTICAST_DELEGATE(FActivatableAbilitiesAddedSignature)


UCLASS()
class GAS_GAME_PROJECT_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputTagHeld(FGameplayTag& InputTag);
	void AbilityInputTagReleased(FGameplayTag& InputTag);
	void InitOwnerAndAvatarActor(AActor* OwnerActor, AActor* AvatarActor);
	void BindCallBackToDependencies();
	void AddStartupAbilities(TArray<TSubclassOf<UBaseGameplayAbility>>, float Level = 1);
	void AddEventReceiver(TSubclassOf<UGameplayAbility> EventReceiverAbilityClass, int32 Level);
	void BindGameplayAttrValChangeCallback(); // Should call BindCallBackToDependencies() instead
	FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayTag GetAbilityStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	void ForEachAbilityDelegate(FForEachAbility Delegate);
	
	FGameplayAttributevalueChangeBroadcastToControllerSignature OnNewAttributeValueChangeBroadcastToControllerDelegate;
	FGameplayEffectTagsBroadcastToControllerSignature GameplayEffectTagsBroadcastToControllerDelegate;
	FActivatableAbilitiesAddedSignature AbilitiesAddedDelegate;

	bool bAbilitiesAdded;
	
private:
	void BindGameplayEffectCallback();
};
