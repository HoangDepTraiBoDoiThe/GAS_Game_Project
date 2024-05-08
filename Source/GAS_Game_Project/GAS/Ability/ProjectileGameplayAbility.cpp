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
	const FRotator ProjectileRotator = (TargetLocation - ICombatInterface::Execute_WeaponLocation(BaseGameCharacter)).Rotation();
	ProjectileTransform.SetLocation(ICombatInterface::Execute_WeaponLocation(BaseGameCharacter));
	ProjectileTransform.SetRotation(ProjectileRotator.Quaternion());
	APawn* Instigator = Cast<APawn>(BaseGameCharacter);
	
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(AbilityProjectileClass, ProjectileTransform, GetOwningActorFromActorInfo(), Instigator);

	FGameplayEffectSpecHandle EffectSpecHandle = MakeMyGameplayEffectSpecHandle();

	Projectile->SetProjectileEffectSpecHandle(EffectSpecHandle);
	Projectile->FinishSpawning(ProjectileTransform);
}
