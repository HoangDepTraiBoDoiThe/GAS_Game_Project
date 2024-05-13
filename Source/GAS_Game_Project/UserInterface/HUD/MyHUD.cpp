// Cu Nhat Hoang


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "GAS_Game_Project/Character/Player/Controller/BasePlayerController.h"
#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"
#include "GAS_Game_Project/UserInterface/UserWidget/BaseUserWidget.h"

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
		GetAttributeMenuWidgetController(NewWidgetControllerStruct);
		check(OverlayWidgetController)
		OverlayWidgetController->BroadCastInitialValue();
		OverlayWidgetController->BroadCastToDependencies();
		OverlayWidgetController->BroadCastAbilityInfoToDependencies();
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

UAttributeMenuWidgetController* AMyHUD::GetAttributeMenuWidgetController(
	const FWidgetControllerParamsStruct& NewWidgetControllerStruct)
{
	if (!AttributeMenuWidgetController)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetupWidgetControllerParams(NewWidgetControllerStruct);		
	}
	return AttributeMenuWidgetController;
}

bool AMyHUD::IsLocallyControlledPlayer(const FWidgetControllerParamsStruct& NewWidgetControllerStruct)
{
	return NewWidgetControllerStruct.PlayerController && NewWidgetControllerStruct.PlayerController.Get()->IsLocalPlayerController();
}
