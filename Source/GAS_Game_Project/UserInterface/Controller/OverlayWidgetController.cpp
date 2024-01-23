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
	AbilitySystemComponent->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddUObject(this, &UOverlayWidgetController::OnNewAttributeValueChangeToView);
	AbilitySystemComponent->GameplayEffectTagsBroadcastToControllerDelegate.AddUObject(this, &ThisClass::OnWidgetMessageDataToView);
}

void UOverlayWidgetController::OnNewAttributeValueChangeToView(const FOnAttributeChangeData& NewAttributeData) const
{
	OnAttributeInitialValuesSignature.Broadcast(NewAttributeData.NewValue, NewAttributeData.Attribute);
}

void UOverlayWidgetController::OnWidgetMessageDataToView(const FGameplayTagContainer& GameplayTagContainer)
{
	for (const FGameplayTag& Tag : GameplayTagContainer)
	{
		OnGameplayEffectWidgetMessageStructToViewDelegate.Broadcast(*GetUIWidgetRowData<FUIWidgetRow>(Tag));
	}
}
