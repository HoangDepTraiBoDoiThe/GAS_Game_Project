// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBaseUserWidget> OverlayWidget;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

private:
	
	
};
