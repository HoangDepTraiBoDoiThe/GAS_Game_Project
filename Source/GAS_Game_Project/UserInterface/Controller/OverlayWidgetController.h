// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayAttributeInitValuesSignature, const float, NewValue, FGameplayAttribute, Attribute);

UCLASS(Blueprintable, BlueprintType)
class GAS_GAME_PROJECT_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()


public:
	virtual void BroadCastInitialValue();
	virtual void BroadCastValueChange();
	void OnNewAttributeValueChangeToController(const FOnAttributeChangeData& NewAttributeData) const;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeInitValuesSignature OnAttributeInitialValuesSignature;

protected:
	
};
