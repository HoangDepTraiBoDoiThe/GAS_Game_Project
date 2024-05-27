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

void UAbilityUIInfoDataAsset::MakeAbilitiesUnlockableOnLeveling(const int32 CharacterLevel, TArray<FAbilityUIInfoStruct>& OUTAbilityUIInfos)
{
	for (FAbilityUIInfoStruct AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.LevelRequireToUnlock <= CharacterLevel && AbilityUIInfoStruct.AbilityAvailabilityStatus == MyGameplayTags::Get().Ability_Availability_NotUnlockable)
		{
			AbilityUIInfoStruct.AbilityAvailabilityStatus = MyGameplayTags::Get().Ability_Availability_Unlockable;
			OUTAbilityUIInfos.AddUnique(AbilityUIInfoStruct);
		}
	}
}

int32 UAbilityUIInfoDataAsset::GetAbilityLevelRequirement(const FGameplayTag& AbilityTag)
{
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return AbilityUIInfoStruct.LevelRequireToUnlock;
		}
	}
	return 0;
}

TSubclassOf<UGameplayAbility> UAbilityUIInfoDataAsset::GetAbilityClass(const FGameplayTag& AbilityTag)
{
	for (FAbilityUIInfoStruct& AbilityUIInfoStruct : AbilityUIInfoStructs)
	{
		if (AbilityUIInfoStruct.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return AbilityUIInfoStruct.AbilityClass;
		}
	}
	return nullptr;
}
