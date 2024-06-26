// Cu Nhat Hoang


#include "MyPlayerState.h"

#include "GAS_Game_Project/Data/XPDataAsset.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
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
	DOREPLIFETIME(AMyPlayerState, AbilityPoint)
	DOREPLIFETIME(AMyPlayerState, SpellPoint)
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

APlayerCharacter* AMyPlayerState::GetPlayerCharacter()
{
	if (!PlayerCharacter) PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	return PlayerCharacter;
}

void AMyPlayerState::SetCharacterXP(const int32 NewXP)
{
	if (!HasAuthority()) return;

	LevelUpIfPossible(NewXP);
	const int32 OldXP = GetCharacterXP();
	CharacterXP = NewXP;
	OnXPChangeDelegate.Broadcast(NewXP, OldXP);
}

void AMyPlayerState::CharacterXPIncreasement(const int32 AdditionXP)
{
	if (!HasAuthority()) return;

	LevelUpIfPossible(AdditionXP);
	const int32 OldXP = GetCharacterXP();
	CharacterXP += AdditionXP;
	OnXPChangeDelegate.Broadcast(CharacterXP, OldXP);
}

void AMyPlayerState::CharacterLevelChange(const int32 AdditionLevel)
{
	if (!HasAuthority()) return;
	
	CharacterLevel += AdditionLevel;
	OnCharacterLevelChangeDelegate.Broadcast(CharacterLevel);
}

void AMyPlayerState::SetCharacterLevel(const int32 NewLevel)
{
	if (!HasAuthority()) return;

	CharacterLevel = NewLevel;
	OnCharacterLevelChangeDelegate.Broadcast(NewLevel);
}

void AMyPlayerState::RewardPlayer(const int32 LevelIncoming)
{
	if (!HasAuthority()) return;
	for (int32 i = 1; i <= LevelIncoming; i++)
	{
		int32 IncomingAttributePoint;
		int32 IncomingAbilityPoint;
		TMap<FGameplayTag, TSubclassOf<UBaseGameplayAbility>> AbilityClassesToGive;
		XPDataAsset->GetRewards(IncomingAttributePoint, IncomingAbilityPoint, AbilityClassesToGive, GetCharacterLevel() + i);
		
		ChangeAttributePoint(IncomingAttributePoint);
		ChangeSpellPoint(IncomingAbilityPoint);
		Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->UpdateAbilitiesStatus(AbilityClassesToGive);
	}
}

void AMyPlayerState::LevelUpIfPossible(int32 IncomingXP)
{
	if (!HasAuthority()) return;

	const int32 CurrentXP = GetCharacterXP();
	const int32 XP2Check = CurrentXP + IncomingXP;
	const int32 LevelIncoming = XPDataAsset->GetLevelByXP(XP2Check, GetCharacterLevel()) - GetCharacterLevel();
	if (LevelIncoming > 0)
	{
		RewardPlayer(LevelIncoming);
		CharacterLevelChange(LevelIncoming);
	}
}

void AMyPlayerState::ChangeAttributePoint(const int32 AdditionAbilityPoint)
{
	if (!HasAuthority()) return;
	AbilityPoint += AdditionAbilityPoint;
	OnAttributePointChangeDelegate.Broadcast(AbilityPoint);
}

void AMyPlayerState::ChangeSpellPoint(const int32 AdditionSpellPoint)
{
	if (!HasAuthority()) return;
	SpellPoint += AdditionSpellPoint;
	OnSpellPointChangeDelegate.Broadcast(SpellPoint);	
}

void AMyPlayerState::Server_UpgradeAbility_Implementation(const FGameplayTag AbilityTag, const int32 UpgradePoint)
{
	ChangeSpellPoint(-UpgradePoint);
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->UpgradeAbility(AbilityTag, UpgradePoint);
}
void AMyPlayerState::Server_SpendAttributePoint_Implementation(const FGameplayTag AttributeTag)
{
	FGameplayEventData PlayLoad = FGameplayEventData();
	PlayLoad.Instigator = GetPawn();
	PlayLoad.EventMagnitude = 1;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), AttributeTag, PlayLoad);
	ChangeAttributePoint(-PlayLoad.EventMagnitude);
}

void AMyPlayerState::RepNotify_CharacterXP(int32 OldXPValue)
{
	OnXPChangeDelegate.Broadcast(CharacterXP, OldXPValue);
}

void AMyPlayerState::RepNotify_CharacterLevel(int32 OldCharacterLevelValue)
{
	OnCharacterLevelChangeDelegate.Broadcast(CharacterLevel);
}

void AMyPlayerState::RepNotify_AbilityPoint(int32 OldAbilityPointValue)
{
	OnAttributePointChangeDelegate.Broadcast(AbilityPoint);
}

void AMyPlayerState::RepNotify_SpellPoint(int32 OldSpellPointValue)
{
	OnSpellPointChangeDelegate.Broadcast(SpellPoint);
}

void AMyPlayerState::BroadCastCharacterExperience()
{
	OnAttributePointChangeDelegate.Broadcast(AbilityPoint);
	OnSpellPointChangeDelegate.Broadcast(SpellPoint);
}

