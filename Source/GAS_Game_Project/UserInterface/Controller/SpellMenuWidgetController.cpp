// Cu Nhat Hoang


#include "SpellMenuWidgetController.h"

#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/Data/XPDataAsset.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/Ability/DamageGameplayAbility.h"

void USpellMenuWidgetController::BroadCastToDependencies()
{
	Super::BroadCastToDependencies();
	
	PlayerState->OnSpellPointChangeDelegate.AddLambda(
		[this] (const int32 SpellPoint)
		{
			OnSpellPointToViewDelegate.Broadcast(SpellPoint);
			SelectSpellGlobe();
		}
	);
	AbilitySystemComponent->OnAbilityStatusChangeDelegate.AddLambda(
			[this] (const FGameplayTag& AbilityStatus, const FGameplayTag AbilityTag, const int32 Level)
			{
				FAbilityUIInfoStruct AbilityUIInfoStruct = Cast<IPlayerInterface>(AbilitySystemComponent->GetAvatarActor())->GetAbilityUIInfoDataAsset()->GetAbilityUIInfoStructByAbilityTag(AbilityTag);
				AbilityUIInfoStruct.AbilityAvailabilityStatus = AbilityStatus;
				AbilityUIInfoToViewDelegate.Broadcast(AbilityUIInfoStruct);
				if (AbilityTag.MatchesTagExact(SelectedSpellButtonTag))
				{
					SelectedSpellStatus = AbilityStatus;
					SelectSpellGlobe();
				}
			}
		);
}

void USpellMenuWidgetController::SelectSpellGlobe()
{
	bool bShouldEnableEquip = false;
	bool bShouldEnableSpendSpellPoint = false;
	ShouldEnableButtons(bShouldEnableEquip, bShouldEnableSpendSpellPoint);
	
	FString CurrentLevelDescription = FString();
	FString NextLevelDescription = FString();
	FGameplayAbilitySpec* AbilitySpecSelectedGlobe = AbilitySystemComponent->GetGameplayAbilitySpecFromTag(GetSelectedSpellButtonTag());
	if (!AbilitySpecSelectedGlobe || SelectedSpellStatus.MatchesTagExact(MyGameplayTags::Get().Ability_Availability_NotUnlockable) || SelectedSpellStatus.MatchesTagExact(MyGameplayTags::Get().Ability_Availability_Unlockable))
	{
		const int32 LevelToUnlock = PlayerState->GeXPDataAsset()->FindAbilityRequireLevelByTag(SelectedSpellButtonTag);
		CurrentLevelDescription = FString::Printf(TEXT("Unlock this spell when you character reached level: <Level>%d</>"), LevelToUnlock);
		NextLevelDescription = FString("Unlock this ability to know more.");
	}
	else
	{
		UDamageGameplayAbility* DamageGameplayAbility = CastChecked<UDamageGameplayAbility>(AbilitySpecSelectedGlobe->Ability.Get());
		const TMap<FGameplayTag, float> Damages = DamageGameplayAbility->GetAbilityDamagesAtLevel(AbilitySpecSelectedGlobe->Level);
		const TMap<FGameplayTag, float> DamagesAtNextLevel = DamageGameplayAbility->GetAbilityDamagesAtLevel(AbilitySpecSelectedGlobe->Level + 1);
		CurrentLevelDescription = FString("Damages of the spell at this level:");
		NextLevelDescription = FString("Damages of the spell at next level:");
		for (const auto& Pair : Damages)
		{
			CurrentLevelDescription += FString::Printf(TEXT("\n<%s>%s: %f</>"), *GetDamageTypeNamesByTag(Pair.Key).ToString(), *GetDamageTypeNamesByTag(Pair.Key).ToString(), Pair.Value);
		}
		for (const auto& Pair : DamagesAtNextLevel)
		{
			NextLevelDescription += FString::Printf(TEXT("\n<%s>%s: %f</>"), *GetDamageTypeNamesByTag(Pair.Key).ToString(), *GetDamageTypeNamesByTag(Pair.Key).ToString(), Pair.Value);
		}
	}
	SelectedSpellGlobeDelegate.Broadcast(bShouldEnableEquip, bShouldEnableSpendSpellPoint, CurrentLevelDescription, NextLevelDescription);
}

FName USpellMenuWidgetController::GetDamageTypeNamesByTag(const FGameplayTag DamageType)
{
	return *MyGameplayTags::Get().DamageTypeNames.Find(DamageType);
}

void USpellMenuWidgetController::ShouldEnableButtons(bool& OutEquipButton, bool& OutSpendSpellPointButton)
{
	const MyGameplayTags MyGameplayTags = MyGameplayTags::Get();
	if (SelectedSpellStatus.MatchesTagExact(MyGameplayTags.Ability_Availability_NotUnlockable))
	{
		OutEquipButton = false;
		OutSpendSpellPointButton = false;
	}
	else if (SelectedSpellStatus.MatchesTagExact(MyGameplayTags.Ability_Availability_Unlockable))
	{
		OutEquipButton = false;
		if (GetSpellPoint() > 0)
			OutSpendSpellPointButton = true;
	}
	else
	{
		OutEquipButton = true;
		if (GetSpellPoint() > 0)
			OutSpendSpellPointButton = true;
	}
}

void USpellMenuWidgetController::SetSelectedSpellButtonTags(const FGameplayTag SpellTag,
                                                            const FGameplayTag SpellStatusTag)
{
	SelectedSpellStatus = SpellStatusTag;
	SelectedSpellButtonTag = SpellTag;
}

void USpellMenuWidgetController::SpendSpellPoint(const int32 PointsToSpend)
{
	if (SelectedSpellButtonTag.IsValid())
		PlayerState->Server_UpgradeAbility(SelectedSpellButtonTag, PointsToSpend);
}

void USpellMenuWidgetController::UnlockAbility(const FGameplayTag& AbilityToUnlock)
{
	
}

int32 USpellMenuWidgetController::GetSpellPoint()
{
	return PlayerState->GetSpellPoint();
}
