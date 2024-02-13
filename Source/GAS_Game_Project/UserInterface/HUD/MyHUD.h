// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GAS_Game_Project/UserInterface/Controller/AttributeMenuWidgetController.h"
#include "GAS_Game_Project/UserInterface/Controller/BaseWidgetController.h"
#include "MyHUD.generated.h"

class UOverlayWidgetController;
class UBaseUserWidget;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();
	void SetupWidget(const FWidgetControllerParamsStruct&);

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParamsStruct& NewWidgetControllerStruct);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParamsStruct& NewWidgetControllerStruct);
	
protected:
	virtual void BeginPlay() override;
	static bool IsLocallyControlledPlayer(const FWidgetControllerParamsStruct& NewWidgetControllerStruct);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget> OverlayWidget;

private:
	
	
};
