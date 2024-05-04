// Cu Nhat Hoang


#include "ProjectileGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "GAS_Game_Project/WorldActor/Projectile/BaseProjectile.h"

void UProjectileGameplayAbility::SpawnProjectile(const FVector TargetLocation) const
{
	if (!GetOwningActorFromActorInfo()->HasAuthority()) return;

	ABaseGameCharacter* BaseGameCharacter = Cast<ABaseGameCharacter>(GetAvatarActorFromActorInfo());
	FTransform ProjectileTransform;
	const FRotator ProjectileRotator = (TargetLocation - BaseGameCharacter->WeaponLocation()).Rotation();
	ProjectileTransform.SetLocation(BaseGameCharacter->WeaponLocation());
	ProjectileTransform.SetRotation(ProjectileRotator.Quaternion());
	APawn* Instigator = Cast<APawn>(BaseGameCharacter);
	
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(AbilityProjectileClass, ProjectileTransform, GetOwningActorFromActorInfo(), Instigator);

	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeEffectContext();
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeapon());

	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeOutgoingSpec(AbilityEffectClass,GetAbilityLevel(), EffectContextHandle);
	for (const TTuple<FGameplayTag, FScalableFloat> Pair : AbilityDamages)
	{
		const float Damage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, Pair.Key, Damage);
	}	

	Projectile->SetProjectileEffectSpecHandle(EffectSpecHandle);
	Projectile->FinishSpawning(ProjectileTransform);
}
