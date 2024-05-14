// Cu Nhat Hoang


#include "AsyncTask_WaitAbilityCooldown.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"

UAsyncTask_WaitAbilityCooldown* UAsyncTask_WaitAbilityCooldown::WaitAbilityCooldown(UAbilitySystemComponent* ASC,
	FGameplayTag CooldownTag)
{
	UAsyncTask_WaitAbilityCooldown* Obj = NewObject<UAsyncTask_WaitAbilityCooldown>();
	if (!ASC || !CooldownTag.IsValid())
	{
		Obj->EndTask();
		return nullptr;
	}
	Obj->OwningASC = ASC;
	Obj->OwningCooldownTag = CooldownTag;

	Obj->OwningASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(Obj, &ThisClass::OnCooldownTagChange);
	Obj->OwningASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(Obj, &ThisClass::OnStartCooldown);
	return Obj;
}

void UAsyncTask_WaitAbilityCooldown::OnCooldownTagChange(const FGameplayTag, const int32 NewCount) const
{
	if (NewCount == 0)
		EndCooldownDelegate.Broadcast(0);
}

void UAsyncTask_WaitAbilityCooldown::OnStartCooldown(UAbilitySystemComponent*, const FGameplayEffectSpec& EffectSpec,
                                                     const FActiveGameplayEffectHandle EffectHandle) const
{
	FGameplayTagContainer GrantedTags;
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllGrantedTags(GrantedTags);
	EffectSpec.GetAllAssetTags(AssetTags);
	if (GrantedTags.HasTagExact(OwningCooldownTag) || AssetTags.HasTagExact(OwningCooldownTag))
	{
		float Duration = OwningASC->GetGameplayEffectDuration(EffectHandle);
		StartCooldownDelegate.Broadcast(Duration);
	}
}

void UAsyncTask_WaitAbilityCooldown::EndTask()
{
	EndCooldownDelegate.Broadcast(0);
	if (OwningASC) OwningASC->RegisterGameplayTagEvent(OwningCooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	MarkAsGarbage();
}
