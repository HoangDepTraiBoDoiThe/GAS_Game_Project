// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

class UBaseWidgetController;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetWidgetController(UBaseWidgetController* NewWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBaseWidgetController> WidgetController;


private:
	
};
