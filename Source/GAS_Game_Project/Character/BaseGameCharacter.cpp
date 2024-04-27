// Cu Nhat Hoang


#include "BaseGameCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"

// Sets default values
ABaseGameCharacter::ABaseGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ACharacter::GetMovementComponent()->bConstrainToPlane = true;
	ACharacter::GetMovementComponent()->bSnapToPlaneAtStart = true;
	ACharacter::GetMovementComponent()->SetIsReplicated(true);
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ABaseGameCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABaseGameCharacter::WeaponLocation()
{
	return GetMesh()->GetSocketByName(WeaponSocketName)->GetSocketLocation(GetMesh());
}

void ABaseGameCharacter::InitAttributeValue()
{
	ApplyGameplayEffectToSelf(DefaultPrimaryAttributesClass);
	ApplyGameplayEffectToSelf(DefaultSecondaryAttributesClass);
	ApplyGameplayEffectToSelf(DefaultVitalAttributesClass);
}

AActor* ABaseGameCharacter::GetWeapon()
{
	if (!Weapon) return this;
	return Cast<AActor>(Weapon);
}

void ABaseGameCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClassToApply) const
{
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClassToApply, CharacterLevel, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

UAbilitySystemComponent* ABaseGameCharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

float ABaseGameCharacter::GetCharacterLevel() { return CharacterLevel; }

