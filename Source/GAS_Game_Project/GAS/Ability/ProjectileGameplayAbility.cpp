// Cu Nhat Hoang


#include "ProjectileGameplayAbility.h"

#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "GAS_Game_Project/WorldActor/Projectile/BaseProjectile.h"

void UProjectileGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UProjectileGameplayAbility::SpawnProjectile()
{
	if (!GetOwningActorFromActorInfo()->HasAuthority()) return;

	ABaseGameCharacter* BaseGameCharacter = Cast<ABaseGameCharacter>(GetAvatarActorFromActorInfo());
	FTransform ProjectileTransform;
	ProjectileTransform.SetLocation(BaseGameCharacter->WeaponLocation());
	APawn* Instigator = Cast<APawn>(BaseGameCharacter);
	
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(
		AbilityProjectileClass, ProjectileTransform, GetOwningActorFromActorInfo(), Instigator);

	Projectile->FinishSpawning(ProjectileTransform);
}
