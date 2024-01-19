// Cu Nhat Hoang


#include "BaseWidgetController.h"

#include "AbilitySystemComponent.h"

UBaseWidgetController::UBaseWidgetController()
{
}

void UBaseWidgetController::SetupWidgetControllerParams(const FWidgetControllerParamsStruct& NewFWidgetControllerParamsStruct)
{
	AttributeSet = NewFWidgetControllerParamsStruct.AttributeSet;
	AbilitySystemComponent = NewFWidgetControllerParamsStruct.AbilitySystemComponent;
	PlayerController = NewFWidgetControllerParamsStruct.PlayerController;
	PlayerState = NewFWidgetControllerParamsStruct.PlayerState;
}
