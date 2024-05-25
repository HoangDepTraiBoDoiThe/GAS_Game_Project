// Cu Nhat Hoang


#include "XPDataAsset.h"

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

void UXPDataAsset::GetRewards(int32& OutAttributePoint, int32& OutAbilityPoint, const int32 RewardAtLevel)
{
	OutAttributePoint = XPInfos[RewardAtLevel].AttributePoint;
	OutAbilityPoint = XPInfos[RewardAtLevel].AbilityPoint;
}

int32 UXPDataAsset::GetXPRequirementForCurrentLevel(const int32 Level)
{
	if (XPInfos.Num() <= 2 || Level == 1) return 0;
	return XPInfos[Level-1].XPRequirementForNextLevel;
}

