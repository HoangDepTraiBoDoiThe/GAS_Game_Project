// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GAS_Game_Project/UserInterface/Controller/AttributeMenuWidgetController.h"
#include "GAS_Game_Project/UserInterface/Controller/BaseWidgetController.h"
#include "MyHUD.generated.h"

class USpellMenuWidgetController;
class UAbilityUIInfoDataAsset;
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
	USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetControllerParamsStruct& NewWidgetControllerStruct);
	
protected:
	virtual void BeginPlay() override;
	static bool IsLocallyControlledPlayer(const FWidgetControllerParamsStruct& NewWidgetControllerStruct);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USpellMenuWidgetController> SpellMenuWidgetControllerClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USpellMenuWidgetController> SpellMenuWidgetController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget> OverlayWidget;


private:
	
	
};
