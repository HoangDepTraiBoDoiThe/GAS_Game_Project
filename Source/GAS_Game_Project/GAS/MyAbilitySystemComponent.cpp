// Cu Nhat Hoang


#include "MyAbilitySystemComponent.h"
#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"

void UMyAbilitySystemComponent::InitOwnerAndAvatarActor(AActor* NewOwnerActor, AActor* NewAvatarActor)
{
	SetOwnerActor(NewOwnerActor);
	SetAvatarActor(NewAvatarActor);
}

void UMyAbilitySystemComponent::BindCallBackToDependencies()
{
	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this] (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle Handle)
		{
			FGameplayTagContainer TagContainer;
			EffectSpec.GetAllAssetTags(TagContainer);
			GameplayEffectTagsBroadcastToControllerDelegate.Broadcast(TagContainer);
		});
	
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
