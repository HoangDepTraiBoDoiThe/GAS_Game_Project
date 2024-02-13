// Cu Nhat Hoang


#include "MyBlueprintFunctionLibrary.h"

#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/UserInterface/HUD/MyHUD.h"


UOverlayWidgetController* UMyBlueprintFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	const FWidgetControllerParamsStruct WidgetControllerParamsStruct = MakeWidgetControllerParamsStruct(WorldContextObject);
	AMyHUD* MyHUD = Cast<AMyHUD>(WidgetControllerParamsStruct.PlayerController->GetHUD());
	return MyHUD->GetOverlayWidgetController(WidgetControllerParamsStruct);
}

UAttributeMenuWidgetController* UMyBlueprintFunctionLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	const FWidgetControllerParamsStruct WidgetControllerParamsStruct = MakeWidgetControllerParamsStruct(WorldContextObject);
	AMyHUD* MyHUD = Cast<AMyHUD>(WidgetControllerParamsStruct.PlayerController->GetHUD());
	checkf(MyHUD, TEXT("Cant get MyHUD"))
	return MyHUD->GetAttributeMenuWidgetController(WidgetControllerParamsStruct);
}

FWidgetControllerParamsStruct UMyBlueprintFunctionLibrary::MakeWidgetControllerParamsStruct(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	checkf(World, TEXT("Cant get World from WorldContextObject"))
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(World->GetFirstLocalPlayerFromController()->GetPlayerController(World));
	checkf(PlayerController, TEXT("Cant get ABasePlayerController"))
	AMyPlayerState* PlayerState = Cast<AMyPlayerState>(PlayerController->GetPlayerState<AMyPlayerState>());
	checkf(PlayerState, TEXT("Cant get PlayerState"))
	UMyAbilitySystemComponent* ASC = Cast<UMyAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());
	UBaseAttributeSet* AttributeSet = Cast<UBaseAttributeSet>(PlayerState->GetAttributeSet());
	checkf(ASC, TEXT("Cant get ASC"))
	checkf(AttributeSet, TEXT("Cant get AttributeSet"))
	return FWidgetControllerParamsStruct(ASC, AttributeSet, PlayerController, PlayerState);
}
