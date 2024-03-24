// Cu Nhat Hoang


#include "BaseGameCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"

// Sets default values
ABaseGameCharacter::ABaseGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ACharacter::GetMovementComponent()->bConstrainToPlane = true;
	ACharacter::GetMovementComponent()->bSnapToPlaneAtStart = true;
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

void ABaseGameCharacter::InitAttributeValue()
{
	Cus_ApplyGameplayEffectToSelf(DefaultPrimaryAttributesClass);
	Cus_ApplyGameplayEffectToSelf(DefaultSecondaryAttributesClass);
	Cus_ApplyGameplayEffectToSelf(DefaultVitalAttributesClass);
}

void ABaseGameCharacter::Cus_ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClassToApply) const
{
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClassToApply, CharacterLevel, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ABaseGameCharacter::ActiveAbilities()
{
	if (!HasAuthority()) return;
	AbilitySystemComponent->AddAbilities(AbilitiesToActive, CharacterLevel);
}

UAbilitySystemComponent* ABaseGameCharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

float ABaseGameCharacter::GetCharacterLevel() { return CharacterLevel; }

