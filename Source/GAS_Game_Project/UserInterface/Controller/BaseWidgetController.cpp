// Cu Nhat Hoang


#include "BaseWidgetController.h"

#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/Data/AbilityUIInforDataAsset.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/Ability/BaseGameplayAbility.h"

class APlayerCharacter;

UBaseWidgetController::UBaseWidgetController()
{
}

void UBaseWidgetController::BroadCastToDependencies()
{
	BroadCastAbilityInfoToDependencies();
}

void UBaseWidgetController::SetupWidgetControllerParams(const FWidgetControllerParamsStruct& NewFWidgetControllerParamsStruct)
{
	AttributeSet = NewFWidgetControllerParamsStruct.AttributeSet;
	AbilitySystemComponent = NewFWidgetControllerParamsStruct.AbilitySystemComponent;
	PlayerController = NewFWidgetControllerParamsStruct.PlayerController;
	PlayerState = NewFWidgetControllerParamsStruct.PlayerState;
}

void UBaseWidgetController::BroadCastCharacterExperience()
{
	PlayerState->BroadCastCharacterExperience();
}

void UBaseWidgetController::BroadCastAbilityInfoToDependencies()
{
	if (AbilitySystemComponent->bAbilitiesAdded) AfterAbilitiesAddedToPlayer(AbilitySystemComponent);
	else AbilitySystemComponent->AbilitiesAddedDelegate.BindUObject(this, &ThisClass::AfterAbilitiesAddedToPlayer);
}

void UBaseWidgetController::AfterAbilitiesAddedToPlayer(const UAbilitySystemComponent* ASC)
{
	IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(AbilitySystemComponent->GetAvatarActor());
	UAbilityUIInfoDataAsset* UIInfoDataAsset = PlayerInterface->GetAbilityUIInfoDataAsset();
	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		const UBaseGameplayAbility* Ability = Cast<UBaseGameplayAbility>(AbilitySpec.Ability);
		if (Ability && Ability->AbilityStartupTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))) && AbilitySystemComponent->GetAvatarActor()->Implements<UPlayerInterface>())
		{
			const FAbilityUIInfoStruct AbilityUIInfoStruct = UIInfoDataAsset->GetAbilityUIInfoStructByInputTag(Cast<UBaseGameplayAbility>(AbilitySpec.Ability)->AbilityStartupTag);
			AbilityUIInfoToViewSignature.Broadcast(AbilityUIInfoStruct);
		}
		else
		{
			for (auto& AbilityTag : AbilitySpec.DynamicAbilityTags)
			{
				if (AbilityTag.MatchesTagExact(MyGameplayTags::Get().Ability_Availability_NotUnlockable))
					continue;
				const FAbilityUIInfoStruct AbilityUIInfoStruct = UIInfoDataAsset->GetAbilityUIInfoStructByInputTag(AbilityTag);
				AbilityUIInfoToViewSignature.Broadcast(AbilityUIInfoStruct);
			}
		}
	}
}
