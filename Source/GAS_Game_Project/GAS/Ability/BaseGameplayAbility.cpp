// Cu Nhat Hoang


#include "BaseGameplayAbility.h"

#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"

UMyAbilitySystemComponent* UBaseGameplayAbility::GetMyASC()
{
	if (!MyASC) MyASC = Cast<UMyAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	return MyASC;
}
