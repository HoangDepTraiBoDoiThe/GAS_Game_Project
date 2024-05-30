// Cu Nhat Hoang


#include "SpellMenuWidgetController.h"

#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"

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
	SelectedSpellGlobeDelegate.Broadcast(bShouldEnableEquip, bShouldEnableSpendSpellPoint, FString("Test"), FString("Test"));

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
