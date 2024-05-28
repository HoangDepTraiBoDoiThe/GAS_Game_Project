// Cu Nhat Hoang


#include "AbilityUIInforDataAsset.h"

FAbilityUIInfoStruct UAbilityUIInfoDataAsset::GetAbilityUIInfoStructByInputTag(
	const FGameplayTag& InputTag, const bool bShouldNotifyIfNotFound)
{
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.InputTag.MatchesTagExact(InputTag))
		{
			return AbilityUIInfoStruct;
		}
	}
	if (bShouldNotifyIfNotFound)
	{
		UE_LOG(LogTemp, Error,
		       TEXT("My Message | UAbilityUIInfoDataAsset | Not Crucial | Cant get [FAbilityUIInfoStruct] in [%S]"),
		       __FUNCTION__)
	}
	return FAbilityUIInfoStruct();
}

FAbilityUIInfoStruct UAbilityUIInfoDataAsset::GetAbilityUIInfoStructByAbilityTag(const FGameplayTag& AbilityTag,
	bool bShouldNotifyIfNotFound)
{
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return AbilityUIInfoStruct;
		}
	}
	if (bShouldNotifyIfNotFound)
	{
		UE_LOG(LogTemp, Error,
			   TEXT("My Message | UAbilityUIInfoDataAsset | Not Crucial | Cant get [FAbilityUIInfoStruct] in [%S]"),
			   __FUNCTION__)
	}
	return FAbilityUIInfoStruct();
}

void UAbilityUIInfoDataAsset::ChangeAbilityStatus(const FGameplayTag& AbilityToChange_Tag,
                                                  const FGameplayTag& StatusTag)
{
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.AbilityTag.MatchesTagExact(AbilityToChange_Tag))
		{
			AbilityUIInfoStruct.AbilityAvailabilityStatus = StatusTag;
		}
	}
}

void UAbilityUIInfoDataAsset::ChangeAbilityInputTag(const FGameplayTag& AbilityToChange_Tag,
                                                    const FGameplayTag& InputTag, const bool bShouldNotifyIfNotFound)
{
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.AbilityTag.MatchesTagExact(AbilityToChange_Tag))
		{
			AbilityUIInfoStruct.InputTag = InputTag;
		}
	}
	if (bShouldNotifyIfNotFound)
	{
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "My Message | UAbilityUIInfoDataAsset | Not Crucial | Cant find [FAbilityUIInfoStruct] with [%s] in [%S]"
		       ), *AbilityToChange_Tag.GetTagName().ToString(), __FUNCTION__)
	}
}

