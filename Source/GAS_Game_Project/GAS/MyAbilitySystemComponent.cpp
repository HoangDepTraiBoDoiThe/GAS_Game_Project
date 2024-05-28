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

void UMyAbilitySystemComponent::AddStartupAbilities(TArray<TSubclassOf<UBaseGameplayAbility>> Abilities, const float Level)
{
	if (!GetAvatarActor()->HasAuthority()) return;
	for (const TSubclassOf<UBaseGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, Level);
		const UBaseGameplayAbility* BaseGameplayAbility = Cast<UBaseGameplayAbility>(AbilitySpec.Ability.Get());
		AbilitySpec.DynamicAbilityTags.AddTag(BaseGameplayAbility->AbilityStartupTag);
		AbilitySpec.DynamicAbilityTags.AddTag(MyGameplayTags::Get().Ability_Availability_Equipped);

		GiveAbility(AbilitySpec);
		MarkAbilitySpecDirty(AbilitySpec);
	}
	AbilitiesAddedDelegate.Broadcast();
	bAbilitiesAdded = true;
}

void UMyAbilitySystemComponent::AddEventReceiver(TSubclassOf<UGameplayAbility> EventReceiverAbilityClass, int32 Level)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(EventReceiverAbilityClass, Level);
	GiveAbilityAndActivateOnce(AbilitySpec);
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

FGameplayTag UMyAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (const FGameplayTag& Tag : AbilitySpec.Ability.Get()->AbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Ability"))))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UMyAbilitySystemComponent::GetAbilityStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (const FGameplayTag& StatusTag : AbilitySpec.DynamicAbilityTags)
	{
		if (StatusTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Ability.Availability"))))
		{
			return StatusTag;
		}
	}
	return FGameplayTag();
}

void UMyAbilitySystemComponent::ForEachAbilityDelegate(FForEachAbility Delegate)
{
	for (const FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if (Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("My message | Failed to execute delegate in %hs"), __FUNCTION__);
		}
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
