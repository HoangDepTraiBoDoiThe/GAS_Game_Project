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
	if (IsLocallyControlledPlayer(NewWidgetControllerStruct))
	{
		GetOverlayWidgetController(NewWidgetControllerStruct);
		check(OverlayWidgetController)
		OverlayWidgetController->BroadCastInitialValue();
		OverlayWidgetController->BroadCastValueChange();
	}
}

UOverlayWidgetController* AMyHUD::GetOverlayWidgetController(const FWidgetControllerParamsStruct& NewWidgetControllerStruct)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(OverlayWidgetControllerClass);
		OverlayWidgetController->SetupWidgetControllerParams(NewWidgetControllerStruct);		
	}
	return OverlayWidgetController;
}

bool AMyHUD::IsLocallyControlledPlayer(const FWidgetControllerParamsStruct& NewWidgetControllerStruct)
{
	return NewWidgetControllerStruct.PlayerController && NewWidgetControllerStruct.PlayerController.Get()->
		IsLocalPlayerController();
}
