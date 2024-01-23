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
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageGameplayTag = FGameplayTag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseUserWidget> MessageWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageTexture2D;
};

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
	static bool IsLocallyControlledPlayer(const FWidgetControllerParamsStruct& NewWidgetControllerStruct);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBaseUserWidget> OverlayWidget;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> UIWidgetRow;

private:
	
	
};
