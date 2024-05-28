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
			NotifySpellPointChangeDelegate.Broadcast(SelectedSpellStatus);
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
					NotifySpellPointChangeDelegate.Broadcast(AbilityStatus);
				}
			}
		);
}

void USpellMenuWidgetController::SetSelectedSpellButtonTags(const FGameplayTag SpellTag,
	const FGameplayTag SpellStatusTag)
{
	SelectedSpellStatus = SpellStatusTag;
	SelectedSpellButtonTag = SpellTag;
}

void USpellMenuWidgetController::SpendSpellPoint(const int32 PointsToSpend)
{
	PlayerState->ChangeSpellPoint(-PointsToSpend);
}

void USpellMenuWidgetController::UnlockAbility(const FGameplayTag& AbilityToUnlock)
{
	
}

int32 USpellMenuWidgetController::GetSpellPoint()
{
	return PlayerState->GetSpellPoint();
}
