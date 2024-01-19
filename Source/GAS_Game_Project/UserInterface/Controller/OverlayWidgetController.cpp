// Cu Nhat Hoang


#include "OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValue()
{
	check (AttributeSet)
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetHitPoint(), AttributeSet->GetHitPointAttribute());
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetMaxHitPoint(), AttributeSet->GetMaxHitPointAttribute());
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetMana(), AttributeSet->GetManaAttribute());
	OnAttributeInitialValuesSignature.Broadcast(AttributeSet->GetMaxMana(), AttributeSet->GetMaxManaAttribute());
}
