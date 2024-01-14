// Cu Nhat Hoang


#include "BaseAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HitPoint, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHitPoint, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always)
}

void UBaseAttributeSet::OnRep_HitPoint(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HitPoint, LastVal)
}

void UBaseAttributeSet::OnRep_MaxHitPoint(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHitPoint, LastVal)
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, LastVal)
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, LastVal)
}
