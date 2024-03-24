// Cu Nhat Hoang


#include "InputDataAsset.h"

#include "InputAction.h"

UInputAction* UInputDataAsset::FindAbilityInputActionByTag(const FGameplayTag& TagToCheck, bool bShouldLog)
{
	for (auto& AbilityInputAction : AbilityInputActions)
		if (AbilityInputAction.InputTag.MatchesTagExact(TagToCheck)) return AbilityInputAction.InputAction;

	if (bShouldLog) UE_LOG(LogTemp, Error, TEXT("Can't find input action tag [%s] of input config [%s]."), *TagToCheck.ToString(), *GetNameSafe(this))
	return nullptr;
}
