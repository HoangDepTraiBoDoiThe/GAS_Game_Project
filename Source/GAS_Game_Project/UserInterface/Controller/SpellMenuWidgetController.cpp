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
}

void USpellMenuWidgetController::SpendSpellPoint(const int32 PointsToSpend)
{
	PlayerState->ChangeSpellPoint(-PointsToSpend);
}

void USpellMenuWidgetController::UnlockAbility(const FGameplayTag& AbilityToUnlock)
{
	TSubclassOf<UGameplayAbility> AbilityClass = PlayerState->GetPlayerCharacter()->GetAbilityUIInfoDataAsset()->GetAbilityClass(AbilityToUnlock);
	PlayerState->GetPlayerCharacter()->GetAbilityUIInfoDataAsset()->ChangeAbilityStatus(AbilityToUnlock, MyGameplayTags::Get().Ability_Availability_Unlocked);
	AbilitySystemComponent->UnlockAbility(AbilityClass);
}
