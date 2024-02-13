// Cu Nhat Hoang


#include "AttributeInfo.h"

FAttributeInfoStruct UAttributeInfo::FindAttributeInfo(const FGameplayTag& GameplayTag)
{
	for (const FAttributeInfoStruct& AttInfo : AttributeInfos) if (AttInfo.AttributeTag.MatchesTagExact(GameplayTag)) return AttInfo;
	return FAttributeInfoStruct();
}
