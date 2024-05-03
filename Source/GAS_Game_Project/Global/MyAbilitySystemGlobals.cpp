// Cu Nhat Hoang


#include "MyAbilitySystemGlobals.h"

#include "GAS_Game_Project/Types/MyGameplayEffectTypes.h"

FGameplayEffectContext* UMyAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FMyGameplayEffectContext();
}
