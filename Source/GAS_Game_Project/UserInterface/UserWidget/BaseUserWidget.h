// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetCloseSignature);

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
	FORCEINLINE void SetWidgetController(UObject* NewWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWidgetCloseSignature OnWidgetCloseDelegate;
	
protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WidgetController;


private:
	
};
