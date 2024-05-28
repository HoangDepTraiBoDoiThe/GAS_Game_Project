// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

class UBaseUserWidget;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifySpellPointChangeSignature, const FGameplayTag, StatusTag);

UCLASS()
class GAS_GAME_PROJECT_API USpellMenuWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadCastToDependencies() override;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FGameplayTag GetSelectedSpellButtonTag() const {return SelectedSpellButtonTag;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSelectedSpellButtonTags(const FGameplayTag SpellTag, const FGameplayTag SpellStatusTag);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSelectedSpellStatus(const FGameplayTag SpellStatus) {SelectedSpellStatus = SpellStatus;}
	UPROPERTY(BlueprintAssignable)
	FOnOnParamToViewSignature OnSpellPointToViewDelegate;

	UFUNCTION(BlueprintCallable)
	void SpendSpellPoint(const int32 PointsToSpend = 1);
	void UnlockAbility(const FGameplayTag& AbilityToUnlock);

	UFUNCTION(BlueprintCallable)
	int32 GetSpellPoint();

	UPROPERTY(BlueprintAssignable)
	FNotifySpellPointChangeSignature NotifySpellPointChangeDelegate;

private:
	FGameplayTag SelectedSpellButtonTag = FGameplayTag();
	FGameplayTag SelectedSpellStatus = FGameplayTag();
	
};
