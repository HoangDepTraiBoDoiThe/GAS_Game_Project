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
		}
	);
	AbilitySystemComponent->OnAbilityStatusChangeDelegate.AddLambda(
			[this] (const FGameplayTag& AbilityStatus, const FGameplayTag AbilityTag, const int32 Level)
			{
				FAbilityUIInfoStruct AbilityUIInfoStruct = Cast<IPlayerInterface>(AbilitySystemComponent->GetAvatarActor())->GetAbilityUIInfoDataAsset()->GetAbilityUIInfoStructByAbilityTag(AbilityTag);
				AbilityUIInfoStruct.AbilityAvailabilityStatus = AbilityStatus;
				AbilityUIInfoToViewDelegate.Broadcast(AbilityUIInfoStruct);
			}
		);
}

void USpellMenuWidgetController::SpendSpellPoint(const int32 PointsToSpend)
{
	PlayerState->ChangeSpellPoint(-PointsToSpend);
}

void USpellMenuWidgetController::UnlockAbility(const FGameplayTag& AbilityToUnlock)
{
	
}
