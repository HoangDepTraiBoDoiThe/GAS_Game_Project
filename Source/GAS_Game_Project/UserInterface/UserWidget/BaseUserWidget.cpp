// Cu Nhat Hoang


#include "BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UObject* NewWidgetController)
{
	WidgetController = NewWidgetController;
	WidgetControllerSet();
}
