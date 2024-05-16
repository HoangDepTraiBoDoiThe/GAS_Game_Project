// Cu Nhat Hoang


#include "MyPlayerState.h"

#include "GAS_Game_Project/Data/XPDataAsset.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "Net/UnrealNetwork.h"


AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("Attribute Set"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	NetUpdateFrequency = 100;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, CharacterXP)
	DOREPLIFETIME(AMyPlayerState, CharacterLevel)
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UXPDataAsset* AMyPlayerState::GeXPDataAsset() const
{
	checkf(XPDataAsset, TEXT("My message | Crucial | XPDataAsset in [PlayState] has not been set yet."))
	return XPDataAsset;
}

void AMyPlayerState::SetCharacterXP(const int32 NewXP)
{
	if (!HasAuthority()) return;

	CharacterXP = NewXP;
	OnXPChangeDelegate.Broadcast(NewXP);
}

void AMyPlayerState::CharacterXPIncreasement(const int32 AdditionXP)
{
	if (!HasAuthority()) return;

	CharacterXP += AdditionXP;
	OnXPChangeDelegate.Broadcast(CharacterXP);
}

void AMyPlayerState::SetCharacterLevel(const int32 NewLevel)
{
	if (!HasAuthority()) return;

	CharacterLevel = NewLevel;
	OnCharacterLevelChangeDelegate.Broadcast(NewLevel);
}

void AMyPlayerState::CharacterLevelIncreasement()
{
	if (!HasAuthority()) return;

	CharacterLevel += 1;
	OnXPChangeDelegate.Broadcast(CharacterLevel);
}

void AMyPlayerState::LevelUpIfPossible(int32 XP)
{
	if (!HasAuthority()) return;

	int32 LevelIncoming = XPDataAsset->GetLevelByXP(XP + GetCharacterXP(), GetCharacterLevel());
	if (LevelIncoming > GetCharacterLevel())
	{
		SetCharacterLevel(LevelIncoming);
	}
}

void AMyPlayerState::RepNotify_CharacterXP(int32 OldXPValue)
{
	OnXPChangeDelegate.Broadcast(CharacterXP);
}

void AMyPlayerState::RepNotify_CharacterLevel(int32 OldCharacterLevelValue)
{
	OnXPChangeDelegate.Broadcast(CharacterLevel);
}
