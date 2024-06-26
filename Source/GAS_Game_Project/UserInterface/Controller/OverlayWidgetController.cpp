// Cu Nhat Hoang


#include "OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "GAS_Game_Project/Data/XPDataAsset.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

UOverlayWidgetController::UOverlayWidgetController()
{

}
void UOverlayWidgetController::BroadCastInitialValue()
{
	check (AttributeSet)
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetHitPoint(), AttributeSet->GetHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetMaxHitPoint(), AttributeSet->GetMaxHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetMana(), AttributeSet->GetManaAttribute());
	OnAttributeValuesSignature.Broadcast(AttributeSet->GetMaxMana(), AttributeSet->GetMaxManaAttribute());
}

void UOverlayWidgetController::BroadCastToDependencies()
{
	Super::BroadCastToDependencies();
	
	AbilitySystemComponent->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddLambda(
		[this] (const FOnAttributeChangeData& NewAttributeData)
		{
			OnAttributeValuesSignature.Broadcast(NewAttributeData.NewValue, NewAttributeData.Attribute);
		});
	
	AbilitySystemComponent->GameplayEffectTagsBroadcastToControllerDelegate.AddLambda(
		[this] (const FGameplayTagContainer& GameplayTagContainer)
		{
			for (const FGameplayTag& Tag : GameplayTagContainer)
			{
				if (const FUIWidgetRow* UIWidgetRow = GetUIWidgetRowData<FUIWidgetRow>(Tag)) OnGameplayEffectWidgetMessageStructToViewDelegate.Broadcast(*UIWidgetRow);
				// else UE_LOG(LogTemp, Error, TEXT("My Message | UOverlayWidgetController | Not critial | UIWidgetRow that associate with tag [%s] was not found. Add row name for all the attributes to fix the issue"), *Tag.GetTagName().ToString())
			}
		});
	PlayerState.Get()->OnXPChangeDelegate.AddLambda(
		[this] (const int32 CharacterXP, int32 OldXP)
		{
			const int32 XPForCurrentLevel = PlayerState.Get()->GeXPDataAsset()->GetXPRequirementForCurrentLevel(PlayerState->GetCharacterLevel());
			const int32 XPForNextLevel = PlayerState.Get()->GeXPDataAsset()->XPInfos[PlayerState->GetCharacterLevel()].XPRequirementForNextLevel;
			const int32 OldLevel = PlayerState.Get()->GeXPDataAsset()->GetLevelByXP(OldXP);
			const int32 CurrentLevel = PlayerState.Get()->GeXPDataAsset()->GetLevelByXP(CharacterXP);
			const int32 Loop = CurrentLevel - OldLevel;
			OnCharacterXPToViewSignature.Broadcast(Loop, CharacterXP, XPForCurrentLevel, XPForNextLevel);
		}
	);
	PlayerState.Get()->OnCharacterLevelChangeDelegate.AddLambda(
	[this] (const int32 CharacterLevel)
		{
			OnCharacterLevelToViewSignature.Broadcast(CharacterLevel);
		}
	);
}

