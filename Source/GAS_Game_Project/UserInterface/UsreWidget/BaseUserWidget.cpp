// Cu Nhat Hoang


#include "BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UBaseWidgetController* NewWidgetController)
{
	WidgetController = NewWidgetController;
	WidgetControllerSet();
}

void UBaseUserWidget::WidgetControllerSet()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("WidgetControllerSet"));
}
