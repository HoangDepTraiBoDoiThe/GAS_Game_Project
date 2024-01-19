// Cu Nhat Hoang


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "GAS_Game_Project/Character/Player/Controller/BasePlayerController.h"
#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"
#include "GAS_Game_Project/UserInterface/UsreWidget/BaseUserWidget.h"

AMyHUD::AMyHUD()
{
	
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

}

void AMyHUD::SetupWidget(const FWidgetControllerParamsStruct& NewWidgetControllerStruct)
{
	OverlayWidget = Cast<UBaseUserWidget>(CreateWidget(GetWorld(), OverlayWidgetClass));
	OverlayWidget->AddToViewport();
	if (OverlayWidget) OverlayWidget->SetWidgetController(GetOverlayWidgetController(NewWidgetControllerStruct));
	if (NewWidgetControllerStruct.PlayerController && NewWidgetControllerStruct.PlayerController.Get()->IsLocalPlayerController())
		GetOverlayWidgetController(NewWidgetControllerStruct)->BroadCastInitialValue();
}

UOverlayWidgetController* AMyHUD::GetOverlayWidgetController(const FWidgetControllerParamsStruct& NewWidgetControllerStruct)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>();
		OverlayWidgetController->SetupWidgetControllerParams(NewWidgetControllerStruct);		
	}
	return OverlayWidgetController;
}
