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
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAbilityStatusChangeSignature, const FGameplayTag& AbilityStatus, const FGameplayTag AbilityTag, const int32 Level)


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
	void UpdateAbilitiesStatus(TMap<FGameplayTag, TSubclassOf<UBaseGameplayAbility>>& AbilityClass);
	void AddEventReceiver(TSubclassOf<UGameplayAbility> EventReceiverAbilityClass, int32 Level);
	void UpgradeAbility(const FGameplayTag AbilityToUpgrade, const int32 UpgradePoints);
	void BindGameplayAttrValChangeCallback(); // Should call BindCallBackToDependencies() instead
	FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayTag GetAbilityStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	void ChangeAbilityStatusTagFromSpec(FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& TagToReplace);
	FGameplayAbilitySpec* GetGameplayAbilitySpecFromTag(const FGameplayTag& AbilityTag);
	void ForEachAbilityDelegate(FForEachAbility Delegate);
	
	FGameplayAttributevalueChangeBroadcastToControllerSignature OnNewAttributeValueChangeBroadcastToControllerDelegate;
	FGameplayEffectTagsBroadcastToControllerSignature GameplayEffectTagsBroadcastToControllerDelegate;
	FActivatableAbilitiesAddedSignature AbilitiesAddedDelegate;
	FOnAbilityStatusChangeSignature OnAbilityStatusChangeDelegate;

	bool bAbilitiesAdded;
	
private:
	UFUNCTION(Client, Reliable)
	void Client_BroadCastAbilityStatusChange(const FGameplayTag& AbilityStatus, const FGameplayTag AbilityTag, const int32 Level);
	virtual void OnRep_ActivateAbilities() override;
	
	void BindGameplayEffectCallback();
};
