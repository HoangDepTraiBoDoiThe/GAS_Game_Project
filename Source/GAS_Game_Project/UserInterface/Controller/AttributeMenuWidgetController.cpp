// Cu Nhat Hoang


#include "AttributeMenuWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
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
	PlayerState->Server_SpendAttributePoint(AttributeTag);
}

void UAttributeMenuWidgetController::BroadCastAttributeValue(const FGameplayTag& Tag, const FGameplayAttribute& GameplayAttribute) const
{
	UAttributeInfo* AttributeInfo = PlayerState->GetAttributeInfo();
	FAttributeInfoStruct WantedAttributeInfoStruct = AttributeInfo->FindAttributeInfo(Tag);
	WantedAttributeInfoStruct.AttributeValue = GameplayAttribute.GetNumericValue(AttributeSet);
	OnGameplayAttributeMenu.Broadcast(WantedAttributeInfoStruct);
}
