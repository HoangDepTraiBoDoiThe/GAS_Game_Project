// Cu Nhat Hoang


#include "BaseWidgetController.h"

#include "AbilitySystemComponent.h"

UBaseWidgetController::UBaseWidgetController()
{
}

void UBaseWidgetController::SetupWidgetController(const FWidgetControllerStruct& NewWidgetControllerStruct)
{
	WidgetControllerStruct = NewWidgetControllerStruct;

}

void UBaseWidgetController::GameplayEffectApplyToSelf(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
}
