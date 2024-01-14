// Cu Nhat Hoang


#include "MyPlayerState.h"

#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"


AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("Attribute Set"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	NetUpdateFrequency = 100;
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
