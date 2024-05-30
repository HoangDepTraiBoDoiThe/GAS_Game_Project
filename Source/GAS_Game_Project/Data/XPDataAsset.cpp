// Cu Nhat Hoang


#include "XPDataAsset.h"

struct FGameplayTag;

int32 UXPDataAsset::GetLevelByXP(const int32 XP, const int32 CurrentLevel)
{
	if (XPInfos.Num() <= 1) return 1;
	if (XPInfos.Num() - 1 <= CurrentLevel) return CurrentLevel;

	for (int32 i = CurrentLevel; i < XPInfos.Num(); i++)
	{
		if (XP < XPInfos[i].XPRequirementForNextLevel)
		{
			return i;
		}
	}
	return 1;
}

void UXPDataAsset::GetRewards(int32& OutAttributePoint, int32& OutAbilityPoint,
	TMap<FGameplayTag, TSubclassOf<UBaseGameplayAbility>>& OutAbilityClasses, const int32 RewardAtLevel)
{
	OutAttributePoint = XPInfos[RewardAtLevel].AttributePoint;
	OutAbilityPoint = XPInfos[RewardAtLevel].AbilityPoint;
	OutAbilityClasses = XPInfos[RewardAtLevel].AbilityClasses;
}

int32 UXPDataAsset::GetXPRequirementForCurrentLevel(const int32 Level)
{
	if (XPInfos.Num() <= 2 || Level == 1) return 0;
	return XPInfos[Level-1].XPRequirementForNextLevel;
}

int32 UXPDataAsset::FindAbilityRequireLevelByTag(const FGameplayTag& AbilityTag, const int32 CharacterCurrentLevel)
{
	for (int32 i = CharacterCurrentLevel; i < XPInfos.Num(); i++)
	{
		for (auto& Pair : XPInfos[i].AbilityClasses)
		{
			if (Pair.Key.MatchesTagExact(AbilityTag))
				return i;
		}
	}
	return 0;
}

