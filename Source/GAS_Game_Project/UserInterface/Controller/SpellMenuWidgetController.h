// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API USpellMenuWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadCastToDependencies() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnOnParamToViewSignature OnSpellPointToViewDelegate;

	UFUNCTION(BlueprintCallable)
	void SpendSpellPoint(const int32 PointsToSpend = 1);
	void UnlockAbility(const FGameplayTag& AbilityToUnlock);
	
};
