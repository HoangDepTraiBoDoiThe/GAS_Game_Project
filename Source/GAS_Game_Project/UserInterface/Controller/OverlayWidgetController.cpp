// Cu Nhat Hoang


#include "OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

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
				else UE_LOG(LogTemp, Error, TEXT("My Message | UOverlayWidgetController | None crucial | UIWidgetRow was not found. Add row name for all the attributes to fix the issue"))
			}
		});
}
