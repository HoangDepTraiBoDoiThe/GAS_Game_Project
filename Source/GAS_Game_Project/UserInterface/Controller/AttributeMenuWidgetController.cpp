// Cu Nhat Hoang


#include "AttributeMenuWidgetController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayAbilityBlueprint.h"
#include "GameplayEffectExtension.h"
#include "GAS_Game_Project/Data/AttributeInfo.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

void UAttributeMenuWidgetController::BroadCastInitialValue()
{
	for (auto& [Key, Value] : AttributeSet->GetAttributeTagMap())
	{
		BroadCastAttributeValue(Key, Value());
	}
}

void UAttributeMenuWidgetController::BroadCastToDependencies()
{
	for (auto& [Key, Value] : AttributeSet->GetAttributeTagMap())
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Value()).AddLambda(
			[this, Key, Value](const FOnAttributeChangeData&)
			{
				BroadCastAttributeValue(Key, Value());
			}
		);
	}
	PlayerState.Get()->OnAttributePointChangeDelegate.AddLambda(
	[this] (const int32 AttributePoint)
	{
		OnAttributePointToViewSignature.Broadcast(AttributePoint);
	}
);
}

void UAttributeMenuWidgetController::ChangeAttributePoint(const int32 AdditionAttributePoint)
{
	PlayerState->ChangeAttributePoint(AdditionAttributePoint);
}

void UAttributeMenuWidgetController::SpendAttributePoint(const FGameplayTag AttributeTag)
{
	FGameplayEventData PlayLoad = FGameplayEventData();
	PlayLoad.Instigator = PlayerState->GetPawn();
	PlayLoad.EventMagnitude = 1;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerState->GetPawn(), AttributeTag, PlayLoad);
	ChangeAttributePoint(-PlayLoad.EventMagnitude);
	
	//FGameplayAttribute Attribute = AttributeSet.Get()->GetAttributeTagMap().Find(AttributeTag)();
	//AbilitySystemComponent->SetNumericAttributeBase(Attribute, Attribute.GetNumericValue(AttributeSet) + 1);
}

void UAttributeMenuWidgetController::BroadCastAttributeValue(const FGameplayTag& Tag, const FGameplayAttribute& GameplayAttribute) const
{
	UAttributeInfo* AttributeInfo = PlayerState->GetAttributeInfo();
	FAttributeInfoStruct WantedAttributeInfoStruct = AttributeInfo->FindAttributeInfo(Tag);
	WantedAttributeInfoStruct.AttributeValue = GameplayAttribute.GetNumericValue(AttributeSet);
	OnGameplayAttributeMenu.Broadcast(WantedAttributeInfoStruct);
}

void UAttributeMenuWidgetController::BroadCastCharacterExperience()
{
	PlayerState->BroadCastCharacterExperience();
}
