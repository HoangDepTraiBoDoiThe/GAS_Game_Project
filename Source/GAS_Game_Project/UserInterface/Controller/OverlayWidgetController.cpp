// Cu Nhat Hoang


#include "OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/Ability/BaseGameplayAbility.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

UOverlayWidgetController::UOverlayWidgetController()
{

}
void UOverlayWidgetController::BroadCastInitialValue()
{
	check (AttributeSet)
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetHitPoint(), AttributeSet->GetHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetMaxHitPoint(), AttributeSet->GetMaxHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetMana(), AttributeSet->GetManaAttribute());
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetMaxMana(), AttributeSet->GetMaxManaAttribute());
}

void UOverlayWidgetController::BroadCastToDependencies()
{
	AbilitySystemComponent->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddLambda(
		[this] (const FOnAttributeChangeData& NewAttributeData)
		{
			OnAttributeValuesSignature.Broadcast(NewAttributeData.NewValue, NewAttributeData.Attribute);
		});
	
	AbilitySystemComponent->GameplayEffectTagsBroadcastToControllerDelegate.AddLambda(
		[this] (const FGameplayTagContainer& GameplayTagContainer)
		{
			for (const FGameplayTag& Tag : GameplayTagContainer)
			{
				if (const FUIWidgetRow* UIWidgetRow = GetUIWidgetRowData<FUIWidgetRow>(Tag)) OnGameplayEffectWidgetMessageStructToViewDelegate.Broadcast(*UIWidgetRow);
				else UE_LOG(LogTemp, Error, TEXT("My Message | UOverlayWidgetController | Not critial | UIWidgetRow that associate with tag [%s] was not found. Add row name for all the attributes to fix the issue"), *Tag.GetTagName().ToString())
			}
		});
}

void UOverlayWidgetController::BroadCastAbilityInfoToDependencies()
{
	if (AbilitySystemComponent->bActivatableAbilitiesAdded) AfterAbilitiesAddedToPlayer(AbilitySystemComponent);
	else AbilitySystemComponent->ActivatableAbilitiesAddedDelegate.BindUObject(this, &ThisClass::AfterAbilitiesAddedToPlayer);
}

void UOverlayWidgetController::AfterAbilitiesAddedToPlayer(const UAbilitySystemComponent* ASC)
{
	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (Cast<UBaseGameplayAbility>(AbilitySpec.Ability)->AbilityStartupTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
		{
			FAbilityUIInfoStruct OutAbilityUIInfoStruct;
			GetAbilityUIInfoStructByInputTag(Cast<UBaseGameplayAbility>(AbilitySpec.Ability)->AbilityStartupTag, OutAbilityUIInfoStruct);
			AbilityUIInfoToViewSignature.Broadcast(OutAbilityUIInfoStruct);
		}
	}
}

void UOverlayWidgetController::GetAbilityUIInfoStructByInputTag(FGameplayTag InputTag,
	FAbilityUIInfoStruct& OUTAbilityUIInfoStruct) const
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(AbilitySystemComponent->GetAvatarActor());
	UAbilityUIInfoDataAsset* DataAsset = PlayerCharacter->GetAbilityUIInfoDataAsset();
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : DataAsset->AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.InputTag.MatchesTagExact(InputTag))
		{
			OUTAbilityUIInfoStruct = AbilityUIInfoStruct;
		}
	}
}


