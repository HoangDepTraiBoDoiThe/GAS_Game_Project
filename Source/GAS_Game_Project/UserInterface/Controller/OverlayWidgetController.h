// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayAttributeDataChangeSignature, const float, NewValue);

UCLASS(Blueprintable, BlueprintType)
class GAS_GAME_PROJECT_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()


public:
	virtual void BroadCastInitialValue();

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeDataChangeSignature OnHealthAttributeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeDataChangeSignature OnMaxHealthAttributeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeDataChangeSignature OnManaAttributeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeDataChangeSignature OnMaxManaAttributeDelegate; 

protected:
	
};
