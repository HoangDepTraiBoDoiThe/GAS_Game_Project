// Cu Nhat Hoang


#include "ProjectileGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "GAS_Game_Project/WorldActor/Projectile/BaseProjectile.h"

void UProjectileGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UProjectileGameplayAbility::SpawnProjectile(FVector TargetLocation)
{
	if (!GetOwningActorFromActorInfo()->HasAuthority()) return;

	ABaseGameCharacter* BaseGameCharacter = Cast<ABaseGameCharacter>(GetAvatarActorFromActorInfo());
	FTransform ProjectileTransform;
	FRotator ProjectileRotator = (TargetLocation - BaseGameCharacter->WeaponLocation()).Rotation();
	ProjectileTransform.SetLocation(BaseGameCharacter->WeaponLocation());
	ProjectileTransform.SetRotation(ProjectileRotator.Quaternion());
	APawn* Instigator = Cast<APawn>(BaseGameCharacter);
	
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(AbilityProjectileClass, ProjectileTransform, GetOwningActorFromActorInfo(), Instigator);

	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeEffectContext();
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeapon());
	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeOutgoingSpec(AbililyEffectClass,GetAbilityLevel(), EffectContextHandle);
	Projectile->SetProjectileEffectSpecHandle(EffectSpecHandle);
	
	Projectile->FinishSpawning(ProjectileTransform);
}
