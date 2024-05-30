// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

class UBaseUserWidget;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSelectedSpellGlobeSignature, const bool, bShouldEnableEquip, const bool, bShouldEnableSpendSpellPoint, const FString, CurrentLevelDes, const FString, NextLvelDes);

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
	FSelectedSpellGlobeSignature SelectedSpellGlobeDelegate;


protected:
	UFUNCTION(BlueprintCallable)
	void SelectSpellGlobe();
	void ShouldEnableButtons(bool& OutEquipButton, bool& OutSpendSpellPointButton);
	static FName GetDamageTypeNamesByTag(const FGameplayTag DamageType);
	
private:
	FGameplayTag SelectedSpellButtonTag = FGameplayTag();
	FGameplayTag SelectedSpellStatus = FGameplayTag();
	
};
