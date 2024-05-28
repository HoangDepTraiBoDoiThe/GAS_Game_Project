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
	if (AbilitySystemComponent->bAbilitiesAdded) BroadCastAbilityUIInfoToDependencies();
	else AbilitySystemComponent->AbilitiesAddedDelegate.AddUObject(this, &ThisClass::BroadCastAbilityUIInfoToDependencies);
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

void UBaseWidgetController::BroadCastAbilityUIInfoToDependencies()
{
	FForEachAbility ForEachAbility;
	IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(PlayerState->GetPawn());
	ForEachAbility.BindLambda(
		[this, PlayerInterface] (const FGameplayAbilitySpec AbilitySpec)
		{
			FAbilityUIInfoStruct AbilityUIInfoStruct = PlayerInterface->GetAbilityUIInfoDataAsset()->GetAbilityUIInfoStructByAbilityTag(AbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			AbilityUIInfoStruct.AbilityAvailabilityStatus = AbilitySystemComponent->GetAbilityStatusTagFromSpec(AbilitySpec);
			AbilityUIInfoToViewDelegate.Broadcast(AbilityUIInfoStruct);
		}
	);
	AbilitySystemComponent->ForEachAbilityDelegate(ForEachAbility);
}
