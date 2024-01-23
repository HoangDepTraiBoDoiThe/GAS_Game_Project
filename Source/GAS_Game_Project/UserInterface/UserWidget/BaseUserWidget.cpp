// Cu Nhat Hoang


#include "BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UBaseWidgetController* NewWidgetController)
{
	WidgetController = NewWidgetController;
	WidgetControllerSet();
}
