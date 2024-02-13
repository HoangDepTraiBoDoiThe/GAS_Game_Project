// Cu Nhat Hoang


#include "OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValue()
{
	check (AttributeSet)
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetHitPoint(), AttributeSet->GetHitPointAttribute());
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetMaxHitPoint(), AttributeSet->GetMaxHitPointAttribute());
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetMana(), AttributeSet->GetManaAttribute());
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetMaxMana(), AttributeSet->GetMaxManaAttribute());
}

void UOverlayWidgetController::BroadCastToDependencies()
{
	AbilitySystemComponent->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddLambda(
		[this] (const FOnAttributeChangeData& NewAttributeData)
		{
			OnAttributeInitialValuesSignature.Broadcast(NewAttributeData.NewValue, NewAttributeData.Attribute);
		});
	
	AbilitySystemComponent->GameplayEffectTagsBroadcastToControllerDelegate.AddLambda(
		[this] (const FGameplayTagContainer& GameplayTagContainer)
		{
			for (const FGameplayTag& Tag : GameplayTagContainer)
			{
				if (const FUIWidgetRow* UIWidgetRow = GetUIWidgetRowData<FUIWidgetRow>(Tag)) OnGameplayEffectWidgetMessageStructToViewDelegate.Broadcast(*UIWidgetRow);
				else UE_LOG(LogTemp, Error, TEXT("Me | UIWidgetRow was not found. Check row name again."))
			}
		});
}
