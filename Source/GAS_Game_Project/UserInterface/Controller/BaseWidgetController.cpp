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
	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySystemComponent->GetAvatarActor()->Implements<UPlayerInterface>())
		{
			for (auto& AbilityStatusTag : AbilitySpec.DynamicAbilityTags)
			{
				if (AbilityStatusTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Ability.Availability"))))
				{
					FGameplayTag AbilityTag = AbilitySpec.Ability->AbilityTags.First();
					IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(AbilitySystemComponent->GetAvatarActor());
					UAbilityUIInfoDataAsset* UIInfoDataAsset = PlayerInterface->GetAbilityUIInfoDataAsset();
					FAbilityUIInfoStruct AbilityUIInfoStruct = UIInfoDataAsset->GetAbilityUIInfoStructByAbilityTag(AbilityTag);
					AbilityUIInfoStruct.AbilityAvailabilityStatus = AbilityStatusTag;
					AbilityUIInfoToViewSignature.Broadcast(AbilityUIInfoStruct);
				}
			}
		}
	}
}
