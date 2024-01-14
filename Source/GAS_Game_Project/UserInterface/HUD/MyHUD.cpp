// Cu Nhat Hoang


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "GAS_Game_Project/UserInterface/UsreWidget/BaseUserWidget.h"

AMyHUD::AMyHUD()
{
	
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

}

void AMyHUD::SetupWidget(const FWidgetControllerStruct& NewWidgetControllerStruct)
{
	OverlayWidget = Cast<UBaseUserWidget>(CreateWidget(GetOwningPlayerController(), OverlayWidgetClass));
	OverlayWidget->AddToViewport();
	if (OverlayWidget) OverlayWidget->SetWidgetController(GetOverlayWidgetController(NewWidgetControllerStruct));
}

UBaseWidgetController* AMyHUD::GetOverlayWidgetController(const FWidgetControllerStruct& NewWidgetControllerStruct)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UBaseWidgetController>();
		OverlayWidgetController->SetupWidgetController(NewWidgetControllerStruct);		
	}
	return OverlayWidgetController;
}
