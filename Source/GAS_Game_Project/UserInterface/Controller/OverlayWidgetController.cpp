// Cu Nhat Hoang


#include "OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValue()
{
	check (AttributeSet)
	OnHealthAttributeDelegate.Broadcast(AttributeSet->GetHitPoint());
}
