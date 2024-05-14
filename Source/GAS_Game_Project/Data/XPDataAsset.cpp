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
