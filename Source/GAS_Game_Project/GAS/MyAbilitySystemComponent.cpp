// Cu Nhat Hoang


#include "MyAbilitySystemComponent.h"

#include "GameplayEffectExtension.h"
#include "Ability/BaseGameplayAbility.h"
#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"

void UMyAbilitySystemComponent::InitOwnerAndAvatarActor(AActor* NewOwnerActor, AActor* NewAvatarActor)
{
	SetOwnerActor(NewOwnerActor);
	SetAvatarActor(NewAvatarActor);
}

void UMyAbilitySystemComponent::BindCallBackToDependencies()
{
	BindGameplayEffectCallback();
	BindGameplayAttrValChangeCallback();
}

void UMyAbilitySystemComponent::AddAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities, const float Level)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, Level);
		if (const UBaseGameplayAbility* BaseGameplayAbility = CastChecked<
			UBaseGameplayAbility>(AbilitySpec.Ability.Get()); BaseGameplayAbility->AbilityStartupTag.IsValid())
		{
			AbilitySpec.DynamicAbilityTags.AddTag(BaseGameplayAbility->AbilityStartupTag);
		}

		GiveAbility(AbilitySpec);
		ActivatableAbilitiesAdded();
	}
}

void UMyAbilitySystemComponent::AddEventReceiver(TSubclassOf<UGameplayAbility> EventReceiverAbilityClass, int32 Level)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(EventReceiverAbilityClass, Level);
	GiveAbilityAndActivateOnce(AbilitySpec);
}

void UMyAbilitySystemComponent::ActivatableAbilitiesAdded()
{
	if (!ActivatableAbilitiesAddedDelegate.ExecuteIfBound(this))
	{
		UE_LOG(LogTemp, Error, TEXT("My Message | UMyAbilitySystemComponent | Not Crucial | No call back functions has been bound to this Delegate [%s]"), *ActivatableAbilitiesAddedDelegate.GetUObject()->GetName())
	}
	bActivatableAbilitiesAdded = true;
}

void UMyAbilitySystemComponent::BindGameplayEffectCallback()
{
	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this] (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle Handle)
		{
			FGameplayTagContainer TagContainer;
			EffectSpec.GetAllAssetTags(TagContainer);
			GameplayEffectTagsBroadcastToControllerDelegate.Broadcast(TagContainer);
		});
}

void UMyAbilitySystemComponent::BindGameplayAttrValChangeCallback()
{
	TArray<FGameplayAttribute> AllAttributes;
	GetAllAttributes(AllAttributes);
	for (const FGameplayAttribute& Attribute : AllAttributes)
	{
		GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
			[this] (const FOnAttributeChangeData& NewAttributeData)
			{
				OnNewAttributeValueChangeBroadcastToControllerDelegate.Broadcast(NewAttributeData);
			});
	}
}

void UMyAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag& InputTag)
{
	for (auto& Ability2Active : GetActivatableAbilities())
	{
		if (Ability2Active.IsActive()) continue;
		if (Ability2Active.DynamicAbilityTags.HasTagExact(InputTag))
		{
			bool bActivated = TryActivateAbility(Ability2Active.Handle);
			AbilitySpecInputPressed(Ability2Active);
		}
	}
}

void UMyAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag& InputTag)
{
	for (auto& Ability2Active : GetActivatableAbilities())
	{
		AbilitySpecInputReleased(Ability2Active);
	}
}
