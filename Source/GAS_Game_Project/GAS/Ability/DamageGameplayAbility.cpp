// Cu Nhat Hoang


#include "DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UDamageGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

FGameplayEffectSpecHandle UDamageGameplayAbility::MakeMyGameplayEffectSpecHandle() const
{
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeEffectContext();
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeapon());
	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeOutgoingSpec(AbilityEffectClass,GetAbilityLevel(), EffectContextHandle);
	for (const TTuple<FGameplayTag, FScalableFloat> Pair : AbilityDamages)
	{
		const float Damage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, Pair.Key, Damage);
	}	
	return EffectSpecHandle;
}

void UDamageGameplayAbility::MakeSphereHitChecker(TArray<AActor*>& OverlapTargetActors, const UObject* WorldContextObject, const TArray<AActor*>& IgnoreActors, AActor* DamageCauser, const FVector& Origin, float DamageOuterRadius)
{
	FCollisionQueryParams SphereParams(SCENE_QUERY_STAT(ApplyRadialDamage),  false, DamageCauser);

	SphereParams.AddIgnoredActors(IgnoreActors);

	// query scene to see what we hit
	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(DamageOuterRadius), SphereParams);
	}
	for (FOverlapResult& Overlap : Overlaps)
	{
		if (!Overlap.GetActor()->Implements<UCombatInterface>())
			continue;
		OverlapTargetActors.AddUnique(Overlap.GetActor());
	}
}

void UDamageGameplayAbility::AppliedMyGameplayEffectToTarget(UAbilitySystemComponent* TargetASC)
{
	const FGameplayEffectSpecHandle SpecHandle = MakeMyGameplayEffectSpecHandle();
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}


